#pragma once

#include <memory>
#include "ICamera.h"

/**********************************************************************************************//**
 * @class	WinCamera
 *
 * @brief	A window camera.
 *
 * @author	liu-wenwu
 * @date	2016/8/31
 **************************************************************************************************/

class WinCamera : public ICamera
{
public:
	WinCamera();
	~WinCamera();


	virtual int count() ;
	virtual bool get_name(int idx, char *buffer, int buff_len);
	virtual bool open(int id) ;
	virtual bool close() ;

	virtual bool is_opened();
	virtual bool get_size(int *width, int *height);

	virtual CameraPara get_camera_para();
	virtual bool read_frame(cv::Mat &frame);

private:
	cv::Ptr<cv::VideoCapture> video_capture;
};

