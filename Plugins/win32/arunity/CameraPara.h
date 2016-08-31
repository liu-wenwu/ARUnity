#ifndef __CAMARAPARA_H__
#define __CAMARAPARA_H__

#include "opencv2/opencv.hpp"


/** @brief	The default horizontal normalized focal length. */
const float default_fdx = 600;
/** @brief	The default vertical normalized focal length. */
const float default_fdy = 600;

/**********************************************************************************************//**
 * @class	CameraPara
 *
 * @brief	A camera parameter.
 *
 * @author	liu-wenwu
 * @date	2016/8/31
 **************************************************************************************************/

class CameraPara
{
public:
	CameraPara();

	void get_projection(cv::Mat &proj);

	void init_default(int width, int height);

	cv::Mat get_camera_matrix(){
		return camera_matrix;
	}
	cv::Mat get_distortion(){
		return distortion;
	}
private:
	/** @brief	the camera internal parameters . */
	cv::Mat camera_matrix;
	/** @brief	the camera distortion parameter. */
	cv::Mat distortion;
};



#endif
