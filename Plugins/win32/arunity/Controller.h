#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <memory>
#include <unordered_map>

#include "opencv2/opencv.hpp"

#include "Common.h"
#include "Marker.h"


class ICamera;


class Controller{

public:

	/**********************************************************************************************//**
	 * @enum	Mode
	 *
	 * @brief	Values that represent modes.
	 **************************************************************************************************/

	enum Mode
	{
		MODE_IDLE,
		MODE_AR,
		MODE_CALIBRATE
	};


	Controller();
	~Controller();

	/**********************************************************************************************//**
	 * @fn	bool Controller::init();
	 *
	 * @brief	Init the controller.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/29
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool init();

	/**********************************************************************************************//**
	 * @fn	bool Controller::release();
	 *
	 * @brief	Releases this object.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/29
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool release();

	/**********************************************************************************************//**
	 * @fn	bool Controller::start_camera();
	 *
	 * @brief	Starts a camera.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/29
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool start_camera();

	/**********************************************************************************************//**
	 * @fn	bool Controller::stop_camera();
	 *
	 * @brief	Stops a camera.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/29
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool stop_camera();

	/**********************************************************************************************//**
	 * @fn	void Controller::start_algo();
	 *
	 * @brief	Starts the algorithm.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/29
	 **************************************************************************************************/

	void start_algorithm();

	/**********************************************************************************************//**
	 * @fn	void Controller::stop_algorithm();
	 *
	 * @brief	Stops the algorithm.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/29
	 **************************************************************************************************/

	void stop_algorithm();

	/**********************************************************************************************//**
	 * @fn	void Controller::set_camera_selector(CAMERA_SELECTOR selector);
	 *
	 * @brief	Set the callback of camera selector.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/29
	 *
	 * @param	selector	the callback of camera selector.
	 **************************************************************************************************/

	void set_camera_selector(CAMERA_SELECTOR selector);

	/**********************************************************************************************//**
	 * @fn	void Controller::set_data_dir(const char *dir);
	 *
	 * @brief	Set data dir.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/29
	 *
	 * @param	dir	The data dir.
	 **************************************************************************************************/

	void set_data_dir(const char *dir);

	/**********************************************************************************************//**
	 * @fn	void Controller::set_camera_para(float *m, float *d);
	 *
	 * @brief	Sets camera parameter.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/29
	 *
	 * @param [in]	m	Camera internal parameters,3x3 matrix.
	 * @param [in]	d	Camera distortion parameters,length is 5.
	 **************************************************************************************************/

	void set_camera_para(float *m, float *d);

	/**********************************************************************************************//**
	 * @fn	void Controller::set_calibrate_chessboard(int rows, int cols, float size);
	 *
	 * @brief	Sets calibrate chessboard.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/29
	 *
	 * @param	rows	The rows of chessboard.
	 * @param	cols	The cols of chessboard.
	 * @param	size	The size of chessboard(m).
	 **************************************************************************************************/

	void set_calibrate_chessboard(int rows, int cols, float size);


	/**********************************************************************************************//**
	 * @fn	void Controller::set_auto_calibrate(bool auto_cali);
	 *
	 * @brief	Sets automatic calibrate.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/29
	 *
	 * @param	auto_cali	true to automatically cali.
	 **************************************************************************************************/

	void set_auto_calibrate(bool auto_cali);

	/**********************************************************************************************//**
	 * @fn	int Controller::get_camera_count();
	 *
	 * @brief	Gets camera count.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/29
	 *
	 * @return	The camera count.
	 **************************************************************************************************/

	int get_camera_count();

	/**********************************************************************************************//**
	 * @fn	bool Controller::get_camera_name(int idx, char *buffer, int buff_len);
	 *
	 * @brief	Gets camera name.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/29
	 *
	 * @param 		  	idx			The index of camera.
	 * @param [in,out]	buffer  	If non-null, the buffer.
	 * @param 		  	buff_len	Length of the buffer.
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool get_camera_name(int idx, char *buffer, int buff_len);

	/**********************************************************************************************//**
	 * @fn	bool Controller::get_camera_size(int *width, int *height);
	 *
	 * @brief	Gets camera size.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/29
	 *
	 * @param [in,out]	width 	If non-null, the width.
	 * @param [in,out]	height	If non-null, the height.
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool get_camera_size(int *width, int *height);

	/**********************************************************************************************//**
	 * @fn	void Controller::update_frame(unsigned int *buffer);
	 *
	 * @brief	Updates the frame described by buffer.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/29
	 *
	 * @param [in,out]	buffer	If non-null, the buffer.
	 **************************************************************************************************/

	void update_frame(unsigned int *buffer);//RGBA

	/**********************************************************************************************//**
	 * @fn	int Controller::get_markers_count();
	 *
	 * @brief	Gets markers count.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/29
	 *
	 * @return	The markers count.
	 **************************************************************************************************/

	int get_markers_count();

	/**********************************************************************************************//**
	 * @fn	void Controller::get_markers_ids(int *ids);
	 *
	 * @brief	Gets markers identifiers.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/29
	 *
	 * @param [in,out]	ids	If non-null, the identifiers.
	 **************************************************************************************************/

	void get_markers_ids(int *ids);

	/**********************************************************************************************//**
	 * @fn	bool Controller::get_marker_tracked(int id);
	 *
	 * @brief	Gets marker tracked.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/29
	 *
	 * @param	id	The identifier.
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool get_marker_tracked(int id);

	/**********************************************************************************************//**
	 * @fn	bool Controller::get_marker_pose(int id, float *mat);
	 *
	 * @brief	Gets marker pose.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/29
	 *
	 * @param 		  	id 	The identifier of marker.
	 * @param	[out]	4x4 mat, the matrix of marker pose.
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool get_marker_pose(int id, float *mat);

	/**********************************************************************************************//**
	 * @fn	void Controller::add_marker(int id, float length);
	 *
	 * @brief	Adds a marker to 'length'.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/29
	 *
	 * @param	id	  	The identifier.
	 * @param	length	The length.
	 **************************************************************************************************/

	void add_marker(int id, float length);

	/**********************************************************************************************//**
	 * @fn	bool Controller::exist_marker(int id);
	 *
	 * @brief	Query whether the marker has been added.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/29
	 *
	 * @param	id	The identifier.
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool exist_marker(int id);

	/**********************************************************************************************//**
	 * @fn	bool Controller::get_projection(float *m,float width, float height, float near_plane, float far_plane);
	 *
	 * @brief	Gets a projection.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/29
	 *
	 * @param	[out]	m		  	If non-null, the projection matrix(4x4).
	 * @param 		  	width	  	The width.
	 * @param 		  	height	  	The height.
	 * @param 		  	near_plane	The near plane.
	 * @param 		  	far_plane 	The far plane.
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool get_projection(float *m,float width, float height, float near_plane, float far_plane);

	/**********************************************************************************************//**
	 * @fn	bool Controller::get_marker_texture(int id, int size, unsigned int *buffer);
	 *
	 * @brief	Get the marker texture.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/29
	 *
	 * @param 		  	id	  	The identifier of marker.
	 * @param 		  	size  	The size of marker image.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool get_marker_texture(int id, int size, char *filepath);

	int get_dictionary_words();

	int get_dictionary();

	void set_dictionary(int dict);

	void draw_result(cv::Mat &img);

private:

	/** @brief	The camera instance. */
	std::shared_ptr<ICamera> camera;

	/** @brief	The data dir. */
	std::string data_dir;

	/** @brief	The camera selector. */
	CAMERA_SELECTOR camera_selector;

	/** @brief	Identifier for the camera. */
	int camera_id;

	int dict_id;
	/** @brief	The dictionary. */
	cv::Ptr<cv::aruco::Dictionary> dictionary;

	/** @brief	The markers. */
	std::unordered_map<int, Marker> markers;

	/**********************************************************************************************//**
	 * @fn	bool Controller::run_calibrate(const cv::Mat &in);
	 *
	 * @brief	Executes the calibrate operation.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/29
	 *
	 * @param	in	The in.
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool run_calibrate(const cv::Mat &in);

	/**********************************************************************************************//**
	 * @fn	void Controller::run_algo(cv::Mat &in);
	 *
	 * @brief	Executes the algo operation.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/29
	 *
	 * @param [in,out]	in	The in.
	 **************************************************************************************************/

	void run_algorithm(cv::Mat &in);

	/**********************************************************************************************//**
	 * @fn	void Controller::estimate_pose(const std::vector< cv::Point2f > &corners, float markerLength, cv::Vec3d &rvec, cv::Vec3d &tvec);
	 *
	 * @brief	Estimate pose of marker.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/30
	 *
	 * @param 		  	corners			The corners.
	 * @param 		  	markerLength	Length of the marker.
	 * @param	[out]	rvec			The rotation vector.
	 * @param	[out]	tvec			The translation vector.
	 **************************************************************************************************/

	void estimate_pose(const std::vector< cv::Point2f > &corners, float markerLength, cv::Vec3d &rvec, cv::Vec3d &tvec);

	void calc_projection(cv::Mat& camera_matrix, float width, float height, float near_plane, float far_plane, float* projection_matrix);


	void calc_modelview(cv::Mat& rotation, cv::Mat& translation, float* model_view_matrix);


	bool auto_calibrate;

	Mode mode;

	bool algo_enabled;


	float projection[16];
};










#endif


