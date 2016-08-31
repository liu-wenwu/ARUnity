#pragma once


#include "CameraPara.h"
#include "Calibrator.h"

/**********************************************************************************************//**
 * @class	ICamera
 *
 * @brief	A camera.
 *
 * @author	liu-wenwu
 * @date	2016/8/31
 **************************************************************************************************/

class ICamera
{
public:
	ICamera() :_calibrated(false)
	{}

	virtual int count()=0;
	virtual bool get_name(int idx,char *buffer,int buff_len) = 0;
	virtual bool open(int id) = 0;
	virtual bool close() = 0;
	virtual bool is_opened()=0;
	virtual bool get_size(int *width,int *height) = 0;

	virtual bool read_frame(cv::Mat &frame)=0;

	virtual CameraPara get_camera_para() = 0;
	//virtual bool set_camera_para(float *m,float *d) = 0;

	bool calibrated(){
		return _calibrated;
	}

	void set_default_para();

	Calibrator & get_calibrator()
	{
		return _calibrator;
	}
protected:

	Calibrator _calibrator;
	CameraPara _camera_para;
	bool _calibrated;

	int _width;
	int _height;
};

