#ifndef __CALIBRATOR_H__
#define __CALIBRATOR_H__


#include "opencv2/opencv.hpp"

class Calibrator
{
public:
	Calibrator();
	~Calibrator();


	bool calibrate(const cv::Mat &gray);

	void set_chessboard(int rows,int cols,float size);


	void init(int width, int height);


private:

	int chessboard_rows;
	int chessboard_cols;
	float chessboard_size;


	std::vector<cv::Point3f> objects;

	std::vector<std::vector<cv::Point3f>> object_points;

	std::vector<std::vector<cv::Point2f>> image_points;


	cv::Mat camera_matrix;
	cv::Mat distortion;
};



#endif