/*

²Î¿¼ÎÄÕÂ£º
http://wiki.opencv.org.cn/index.php/%e4%bd%bf%e7%94%a8DirectShow%e9%87%87%e9%9b%86%e5%9b%be%e5%83%8f#.E4.B8.8B.E8.BD.BD

*/



#include "WinCamera.h"



#include <atlbase.h>
#include <dshow.h>

#pragma comment(lib,"Strmiids.lib") 



WinCamera::WinCamera()
{
	video_capture = cv::makePtr<cv::VideoCapture>();
}


WinCamera::~WinCamera()
{
}



int WinCamera::count()
{
	int count = 0;
	CoInitialize(NULL);

	CComPtr<ICreateDevEnum> pCreateDevEnum;
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, (void**)&pCreateDevEnum);

	CComPtr<IEnumMoniker> pEm;
	hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEm, 0);
	if (hr != NOERROR)
	{
		return count;
	}

	pEm->Reset();
	ULONG cFetched;
	IMoniker *pM;
	while (hr = pEm->Next(1, &pM, &cFetched), hr == S_OK)
	{
		count++;
	}

	pCreateDevEnum = NULL;
	pEm = NULL;
	return count;

}


bool WinCamera::get_name(int idx, char *buffer, int buff_len)
{

	int count = 0;
	CoInitialize(NULL);

	// enumerate all video capture devices
	CComPtr<ICreateDevEnum> pCreateDevEnum;
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, (void**)&pCreateDevEnum);

	CComPtr<IEnumMoniker> pEm;
	hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEm, 0);
	if (hr != NOERROR)
		return false;

	pEm->Reset();
	ULONG cFetched;
	IMoniker *pM;
	while (hr = pEm->Next(1, &pM, &cFetched), hr == S_OK)
	{
		if (count == idx)
		{
			IPropertyBag *pBag = 0;
			hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
			if (SUCCEEDED(hr))
			{
				VARIANT var;
				var.vt = VT_BSTR;
				hr = pBag->Read(L"FriendlyName", &var, NULL);
				if (hr == NOERROR)
				{
					WideCharToMultiByte(CP_ACP, 0, var.bstrVal, -1, buffer, buff_len, "", NULL);
					SysFreeString(var.bstrVal);
				}
				pBag->Release();
			}
			pM->Release();

			break;
		}
		count++;
	}

	pCreateDevEnum = NULL;
	pEm = NULL;

	return true;

}



bool WinCamera::open(int id)
{
	bool ok = video_capture->open(id);

	_width = video_capture->get(cv::CAP_PROP_FRAME_WIDTH);
	_height = video_capture->get(cv::CAP_PROP_FRAME_HEIGHT);

	_camera_para.init_default(_width, _height);

	return ok;
}

bool WinCamera::close()
{
	video_capture->release();
	return true;
}

bool WinCamera::read_frame(cv::Mat &frame)
{
	if (video_capture->isOpened() && video_capture->read(frame))
		return true;
	else
		return false;
}

bool WinCamera::is_opened()
{
	return video_capture->isOpened();
}


bool WinCamera::get_size(int *width, int *height)
{
	if (!is_opened())
		return false;

	*width = _width;
	*height = _height;

	return true;
}



CameraPara  WinCamera::get_camera_para()
{
	return _camera_para;
}

