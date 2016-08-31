
#include "ARUnity.h"
#include "Controller.h"
#include "Logger.h"
#include <cstdarg>
#include "opencv2/opencv.hpp"

static Controller gController;


extern "C"
{


	ARUNITY_API bool start_camera()
	{
		return gController.start_camera();
	}

	ARUNITY_API bool stop_camera()
	{
		return gController.stop_camera();
	}

	ARUNITY_API void start_algorithm()
	{
		return gController.start_algorithm();
	}

	ARUNITY_API void stop_algorithm()
	{
		return gController.stop_algorithm();
	}


	ARUNITY_API int get_camera_count()
	{
		return gController.get_camera_count();
	}

	ARUNITY_API bool get_camera_name(int idx, char *buffer, int buff_len)
	{
		return gController.get_camera_name(idx, buffer, buff_len);
	}
	ARUNITY_API void set_camera_selector(CAMERA_SELECTOR selector)
	{
		gController.set_camera_selector(selector);
	}


	ARUNITY_API void register_logger(LOGCALLBACK callback)
	{
		Logger::set_callback(callback);
	}


	ARUNITY_API bool get_camera_size(int *width, int *height)
	{
		return gController.get_camera_size(width, height);

	}

	ARUNITY_API void update_camera_frame(unsigned int *buffer)
	{
		gController.update_frame(buffer);

	}


	ARUNITY_API int get_markers_count()
	{
		return gController.get_markers_count();
	}

	ARUNITY_API void get_markers_ids(int* ids)
	{
		return gController.get_markers_ids(ids);
	}

	ARUNITY_API bool get_marker_pose(int id, float *mat)
	{
		return gController.get_marker_pose(id, mat);
	}

	ARUNITY_API void add_marker(int id, float length)
	{
		return gController.add_marker(id, length);
	}


	ARUNITY_API bool exist_marker(int id)
	{
		return gController.exist_marker(id);
	}


	ARUNITY_API bool get_projection(float *m, float width, float height, float near_plane, float far_plane)
	{
		return gController.get_projection(m, width, height, near_plane, far_plane);
	}



	ARUNITY_API bool get_marker_texture(int id, int size, char *filepath)
	{
		return gController.get_marker_texture(id, size, filepath);
	}




	ARUNITY_API bool test_update_camera_frame(unsigned int *buffer)
	{
		update_camera_frame(buffer);
		int width;
		int height;
		if (!get_camera_size(&width, &height))
			return false;

		cv::Mat frame(cv::Size(width, height), CV_8UC4, buffer);
		cv::cvtColor(frame, frame, CV_RGBA2BGR);

		imshow("test", frame);

		int key = cvWaitKey(30);

		if (key == 32)
			return false;

		return true;
	}


	ARUNITY_API void set_dictionary(int dict)
	{
		gController.set_dictionary(dict);
	}

	ARUNITY_API int get_dictionary()
	{
		return gController.get_dictionary();
	}

	ARUNITY_API int get_dictionary_words()
	{
		return gController.get_dictionary_words();
	}

}

