#pragma once
#include "ICamera.h"

/**********************************************************************************************//**
 * @class	EmptyCamera
 *
 * @brief	An empty camera.
 *
 * @author	liu-wenwu
 * @date	2016/8/31
 **************************************************************************************************/

class EmptyCamera :
	public ICamera
{
public:


	int count()
	{
		return 0;
	}
	bool get_name(int idx, char *buffer, int buff_len)
	{
		return false;
	}
	bool open(int id)
	{
		return false;
	}
	bool close()
	{
		return false;
	}
	bool read_frame(cv::Mat &frame)
	{
		return false;
	}

};

