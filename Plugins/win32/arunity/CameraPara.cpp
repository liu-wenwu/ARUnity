#include "CameraPara.h"



CameraPara::CameraPara()
{
	camera_matrix.create(3, 3, CV_32FC1);
	camera_matrix.setTo(0);
	*camera_matrix.ptr<float>(0, 0) = 1000;
	*camera_matrix.ptr<float>(1, 1) = 1000;
	*camera_matrix.ptr<float>(2, 2) = 1;


	distortion.create(1, 5, CV_32FC1);
	distortion.setTo(0);

}



void CameraPara::init_default(int width, int height)
{
	*camera_matrix.ptr<float>(0, 2) = width / 2;
	*camera_matrix.ptr<float>(1, 2) = height / 2;
}