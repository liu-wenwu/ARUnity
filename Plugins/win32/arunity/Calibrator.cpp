
#include "Calibrator.h"


Calibrator::Calibrator()
{
	camera_matrix.create(3, 3, CV_32FC1);
	distortion.create(1, 5, CV_32FC1);

	set_chessboard(9,9,0.061);
}


Calibrator::~Calibrator()
{

}

void Calibrator::init(int width,int height)
{


}


void Calibrator::set_chessboard(int rows, int cols, float size)
{
	assert(rows > 0 && cols > 0 && size > 0);

	chessboard_rows = rows;
	chessboard_cols = cols;
	chessboard_size = size;

	objects.clear();

	cv::Point3f obj;
	for (int j = 0; j < chessboard_rows; j++) {
		for (int k = 0; k < chessboard_cols; k++) {
			obj.x = j * chessboard_size;
			obj.y = k * chessboard_size;
			obj.z = 0.0;
			objects.push_back(obj);
		}
	}

}

bool Calibrator::calibrate(const cv::Mat &gray)
{

	std::vector<cv::Mat> rotation;
	std::vector<cv::Mat> translation;


	std::vector<cv::Point2f> corners;
	bool found = cv::findChessboardCorners(gray, cv::Size(chessboard_rows, chessboard_cols), corners);


	if (found)
	{
		std::cout << "calibrate count:" << image_points.size() << std::endl;

		
		cornerSubPix(gray, corners, cv::Size(3, 3), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03));

		image_points.push_back(corners);
		object_points.push_back(objects);


		if (image_points.size() > 5)
		{
			std::cout << "calibrate ok" << std::endl;

			calibrateCamera(object_points, image_points, gray.size(), camera_matrix, distortion, rotation, translation);
			std::cout << "camera_matrix" << std::endl;
			std::cout << camera_matrix << std::endl;
			std::cout << "distortion" << std::endl;
			std::cout << distortion << std::endl;


			cv::FileStorage fs("D:/camera.yml", cv::FileStorage::WRITE);
			fs << "cameraMatrix" << camera_matrix;
			fs << "distortion" << distortion;
			fs.release();

			return true;
		}
	}


	return false;
}