#include "Controller.h"
#include "WinCamera.h"
#include "ICamera.h"
#include "Logger.h"

#include "opencv2/opencv.hpp"
#include "opencv2/aruco.hpp"

using namespace cv;

Controller::Controller()
:camera_selector(nullptr), 
camera_id(0),
mode(MODE_IDLE),
dict_id(cv::aruco::DICT_7X7_1000)
{
#ifdef WIN32
	camera = std::make_shared<WinCamera>();
#else
	camera =std::make_shared<EmptyCamera>();
#endif


	dictionary = cv::aruco::getPredefinedDictionary(dict_id);


	auto_calibrate = false;

	algo_enabled = false;
}


Controller::~Controller()
{
}



bool Controller::init()
{
	return true;
}

bool Controller::release()
{
	return true;
}

bool Controller::start_camera()
{
	if (camera->is_opened())
		return true;

	if (camera_selector)
		camera_id = camera_selector();

	if (camera_id < 0 || camera_id >= get_camera_count())
		return false;

	return camera->open(camera_id);
}

bool Controller::stop_camera()
{
	return true;
}

void Controller::start_algorithm()
{
	algo_enabled = true;
}
void Controller::stop_algorithm()
{
	algo_enabled = false;
}

void Controller::set_data_dir(const char *dir)
{
	data_dir = dir;
}

void Controller::set_camera_selector(CAMERA_SELECTOR selector)
{
	camera_selector = selector;
}



int Controller::get_camera_count()
{
	return camera->count();
}

bool Controller::get_camera_name(int idx, char *buffer, int buff_len)
{
	return camera->get_name(idx, buffer, buff_len);
}


void Controller::update_frame(unsigned int *buffer)
{
	cv::Mat frame;
	cv::Mat out(cv::Size(640, 480), CV_8UC4, buffer);
	cv::Mat result;

	camera->read_frame(frame);


	if (mode == MODE_IDLE)
	{
		if (!camera->calibrated())
		{

			if (!auto_calibrate || (auto_calibrate && run_calibrate(frame)))
			{
				mode = MODE_AR;

			}

		}
		else
			mode = MODE_AR;
	}
	else if (mode == MODE_AR && algo_enabled)
	{
		run_algorithm(frame);
	}
	else
	{
	}

	cv::cvtColor(frame, out, CV_BGR2RGBA);

}


bool Controller::get_camera_size(int *width, int *height)
{
	return camera->get_size(width, height);

}




int Controller::get_markers_count()
{
	return markers.size();
}


void Controller::get_markers_ids(int *ids)
{
	assert(ids != NULL);

	for (std::unordered_map<int, Marker>::iterator iter = markers.begin(); iter != markers.end(); ++iter)
	{
		*(ids++) = iter->first;
	}

}



bool Controller::get_marker_pose(int id, float *mat)
{
	assert(id>=0 && mat!=NULL);

	std::unordered_map<int, Marker>::iterator iter = markers.find(id);

	if (iter == markers.end() || !iter->second.get_tracked())
		return false;

	iter->second.get_pose(mat);

	return true;

}



void Controller::add_marker(int id, float length)
{
	if (id < 0 || length <= 0)
		return;

	std::unordered_map<int, Marker>::iterator iter = markers.find(id);
	if (iter == markers.end())
		markers.insert(std::make_pair(id, Marker(id, length)));
	else
	{
		Marker &marker = iter->second;
		marker.set_length(length);
	}


}

bool Controller::exist_marker(int id)
{
	return  id >= 0 && markers.find(id) != markers.end();
}


bool Controller::get_projection(float *m, float width, float height, float near_plane, float far_plane)
{
	Mat camera_matrix = camera->get_camera_para().get_camera_matrix();

	if (camera_matrix.empty())
		return false;

	calc_projection(camera_matrix, width, height, near_plane, far_plane, m);
}



void Controller::estimate_pose(const std::vector< cv::Point2f > &corners, float markerLength, Vec3d &rvec, Vec3d &tvec)
{
	Mat objPoints;
	objPoints.create(4, 1, CV_32FC3);
	// set coordinate system in the middle of the marker, with Z pointing out
	objPoints.ptr< Vec3f >(0)[0] = Vec3f(-markerLength / 2.f, markerLength / 2.f, 0);
	objPoints.ptr< Vec3f >(0)[1] = Vec3f(markerLength / 2.f, markerLength / 2.f, 0);
	objPoints.ptr< Vec3f >(0)[2] = Vec3f(markerLength / 2.f, -markerLength / 2.f, 0);
	objPoints.ptr< Vec3f >(0)[3] = Vec3f(-markerLength / 2.f, -markerLength / 2.f, 0);


	cv::Mat cam_mat = camera->get_camera_para().get_camera_matrix();
	cv::Mat cam_dis = camera->get_camera_para().get_distortion();

	//rvec,tvec一定要是double类型
	cv::solvePnP(objPoints, corners, cam_mat, cam_dis, rvec, tvec);

}


void Controller::run_algorithm(cv::Mat &in)
{
	
	CameraPara para = camera->get_camera_para();
	cv::Mat camera_matrix = para.get_camera_matrix();
	cv::Mat distortion = para.get_distortion();


	std::vector<cv::KeyPoint>  keypoints;
	cv::Mat gray;
	cv::cvtColor(in, gray, CV_BGR2GRAY);


	std::vector< int > ids;
	std::vector< std::vector< cv::Point2f > > corners;

	cv::aruco::detectMarkers(gray, dictionary, corners, ids);


	for (std::unordered_map<int, Marker>::iterator iter = markers.begin(); iter != markers.end(); ++iter)
	{
		iter->second.set_tracked(false);
	}

	if (ids.size() > 0 && markers.size() > 0)
	{

		for (int i = 0; i < ids.size(); ++i)
		{

			std::unordered_map<int, Marker>::iterator iter = markers.find(ids[i]);
			if (iter == markers.end())
				continue;

			Marker &marker = iter->second;

			cv::Vec3d rvec, tvec;
			estimate_pose(corners[i], marker.length(), rvec, tvec);

			//aruco::drawAxis(in, camera_matrix, distortion, rvec, tvec, marker.length() / 2);

		
			marker.set_tracked(true);

			Mat rmat;
			Rodrigues(rvec, rmat);

			Mat tmat(3, 1, CV_64FC1);
			tmat.at<double>(0, 0) = tvec[0];
			tmat.at<double>(1, 0) = tvec[1];
			tmat.at<double>(2, 0) = tvec[2];

			float modelview[16];


			calc_modelview(rmat, tmat, modelview);


			marker.set_pose(modelview);
	

		}

	}


}


bool Controller::run_calibrate(const cv::Mat &in)
{
	Mat gray;
	cv::cvtColor(in, gray, CV_BGR2GRAY);
	return camera->get_calibrator().calibrate(gray);
}



void Controller::calc_projection(cv::Mat& camera_matrix, float width, float height, float near_plane, float far_plane, float* projection_matrix)
{

	float f_x = camera_matrix.at<float>(0, 0);
	float f_y = camera_matrix.at<float>(1, 1);

	float c_x = camera_matrix.at<float>(0, 2);
	float c_y = camera_matrix.at<float>(1, 2);
	

	projection_matrix[0] = 2 * f_x / width;
	projection_matrix[1] = 0.0f;
	projection_matrix[2] = 0.0f;
	projection_matrix[3] = 0.0f;

	projection_matrix[4] = 0.0f;
	projection_matrix[5] = 2 * f_y / height;
	projection_matrix[6] = 0.0f;
	projection_matrix[7] = 0.0f;

	projection_matrix[8] = 1.0f - 2 * c_x / width;
	projection_matrix[9] = 2 * c_y / height - 1.0f;
	projection_matrix[10] = -(far_plane + near_plane) / (far_plane - near_plane);
	projection_matrix[11] = -1.0f;

	projection_matrix[12] = 0.0f;
	projection_matrix[13] = 0.0f;
	projection_matrix[14] = -2.0f*far_plane*near_plane / (far_plane - near_plane);
	projection_matrix[15] = 0.0f;
}


void Controller::calc_modelview(cv::Mat& rotation, cv::Mat& translation, float* model_view_matrix)
{
	//CV坐标系转opengl坐标系，旋转180°

	static double d[] =
	{
		1, 0, 0,
		0, -1, 0,
		0, 0, -1
	};
	Mat_<double> rx(3, 3, d);

	rotation = rx*rotation;
	translation = rx*translation;
	

	model_view_matrix[0] = rotation.at<double>(0, 0);
	model_view_matrix[1] = rotation.at<double>(1, 0);
	model_view_matrix[2] = rotation.at<double>(2, 0);
	model_view_matrix[3] = 0.0f;

	model_view_matrix[4] = rotation.at<double>(0, 1);
	model_view_matrix[5] = rotation.at<double>(1, 1);
	model_view_matrix[6] = rotation.at<double>(2, 1);
	model_view_matrix[7] = 0.0f;

	model_view_matrix[8] = rotation.at<double>(0, 2);
	model_view_matrix[9] = rotation.at<double>(1, 2);
	model_view_matrix[10] = rotation.at<double>(2, 2);
	model_view_matrix[11] = 0.0f;

	model_view_matrix[12] = translation.at<double>(0, 0);
	model_view_matrix[13] = translation.at<double>(1, 0);
	model_view_matrix[14] = translation.at<double>(2, 0);
	model_view_matrix[15] = 1.0f;

}




bool Controller::get_marker_texture(int id, int size, char *filepath)
{
	if (id < 0 || size <= 0 || filepath == NULL)
		return false;

	Mat img;
	Marker::get_image(img,id,size,dictionary);
	if (img.empty() || img.rows==0 ||img.cols==0)
		return false;

	imwrite(filepath, img);

	return true;
}


static int dict_words[17] = {
	50,//DICT_4X4_50 = 0
	100,//DICT_4X4_100
	250,//DICT_4X4_250
	1000,//DICT_4X4_1000
	50,//DICT_5X5_50
	100,//DICT_5X5_100
	250,//DICT_5X5_250
	1000,//DICT_5X5_1000
	50,//DICT_6X6_50
	100,//DICT_6X6_100
	250,//DICT_6X6_250
	100,//DICT_6X6_1000
	50,//DICT_7X7_50
	100,//DICT_7X7_100
	250,//DICT_7X7_250
	1000,//DICT_7X7_1000
	1024//DICT_ARUCO_ORIGINAL=16
};

int Controller::get_dictionary_words()
{
	return dict_words[dict_id];
}

int Controller::get_dictionary()
{
	return dict_id;
}



void Controller::set_dictionary(int dict)
{
	if (dict<0 || dict>16)
		return;

	dict_id = dict;
	dictionary = cv::aruco::getPredefinedDictionary(dict_id);
}