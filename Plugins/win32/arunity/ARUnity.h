/*
*	基于OpenCV的Unity的图像处理框架
*	作者：liu-wenwu ,UESTC AA
*/

#ifndef __CVUNITY_H__
#define __CVUNITY_H__

#ifdef CVUNITY_EXPORTS
#define ARUNITY_API __declspec(dllexport)
#else
#define ARUNITY_API __declspec(dllimport)
#endif


#include "Common.h"


extern "C"
{

	/**********************************************************************************************//**
	 * @fn	ARUNITY_API bool start_camera();
	 *
	 * @brief	Starts a camera.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/31
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	ARUNITY_API bool start_camera();

	/**********************************************************************************************//**
	 * @fn	ARUNITY_API bool stop_camera();
	 *
	 * @brief	Stops a camera.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/31
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	ARUNITY_API bool stop_camera();

	/**********************************************************************************************//**
	 * @fn	ARUNITY_API void start_algorithm();
	 *
	 * @brief	Starts an algorithm.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/31
	 **************************************************************************************************/

	ARUNITY_API void start_algorithm();

	/**********************************************************************************************//**
	 * @fn	ARUNITY_API void stop_algorithm();
	 *
	 * @brief	Stops an algorithm.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/31
	 **************************************************************************************************/

	ARUNITY_API void stop_algorithm();

	/**********************************************************************************************//**
	 * @fn	ARUNITY_API void register_logger(LOGCALLBACK callback);
	 *
	 * @brief	Registers the logger callback.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/31
	 *
	 * @param	callback	The callback.
	 **************************************************************************************************/

	ARUNITY_API void register_logger(LOGCALLBACK callback);

	/**********************************************************************************************//**
	 * @fn	ARUNITY_API void set_camera_selector(CAMERA_SELECTOR selector);
	 *
	 * @brief	Sets camera selector.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/31
	 *
	 * @param	selector	The selector.
	 **************************************************************************************************/

	ARUNITY_API void set_camera_selector(CAMERA_SELECTOR selector);

	/**********************************************************************************************//**
	 * @fn	ARUNITY_API int get_camera_count();
	 *
	 * @brief	Gets camera count.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/31
	 *
	 * @return	The camera count.
	 **************************************************************************************************/

	ARUNITY_API int get_camera_count();

	/**********************************************************************************************//**
	 * @fn	ARUNITY_API bool get_camera_name(int idx, char *buffer, int buff_len);
	 *
	 * @brief	Gets camera name.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/31
	 *
	 * @param 		  	idx			The index.
	 * @param	[out]	buffer  	If non-null, the buffer.
	 * @param 		  	buff_len	Length of the buffer.
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	ARUNITY_API bool get_camera_name(int idx, char *buffer, int buff_len);

	/**********************************************************************************************//**
	 * @fn	ARUNITY_API bool get_camera_size(int *width, int *height);
	 *
	 * @brief	Gets camera size.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/31
	 *
	 * @param	[out]	width 	If non-null, the width.
	 * @param	[out]	height	If non-null, the height.
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	ARUNITY_API bool get_camera_size(int *width, int *height);

	/**********************************************************************************************//**
	 * @fn	ARUNITY_API void update_camera_frame(unsigned int *buffer);
	 *
	 * @brief	Updates the camera frame.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/31
	 *
	 * @param	 [out]	buffer	If non-null, the buffer.
	 **************************************************************************************************/

	ARUNITY_API void update_camera_frame(unsigned int *buffer);

	/**********************************************************************************************//**
	 * @fn	ARUNITY_API int get_markers_count();
	 *
	 * @brief	Gets markers count.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/31
	 *
	 * @return	The markers count.
	 **************************************************************************************************/

	ARUNITY_API int get_markers_count();

	/**********************************************************************************************//**
	 * @fn	ARUNITY_API void get_markers_ids(int* ids);
	 *
	 * @brief	Gets markers identifiers.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/31
	 *
	 * @param [in,out]	ids	If non-null, the identifiers.
	 **************************************************************************************************/

	ARUNITY_API void get_markers_ids(int* ids);

	/**********************************************************************************************//**
	 * @fn	ARUNITY_API bool get_marker_pose(int id, float *mat);
	 *
	 * @brief	Gets marker pose.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/31
	 *
	 * @param 		  	id 	The identifier.
	 * @param [in,out]	mat	If non-null, the matrix.
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	ARUNITY_API bool get_marker_pose(int id, float *mat);

	/**********************************************************************************************//**
	 * @fn	ARUNITY_API bool get_projection(float *m, float width, float height, float near_plane, float far_plane);
	 *
	 * @brief	Gets a projection.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/31
	 *
	 * @param	[out]	m		  	If non-null, the float to process.
	 * @param 		  	width	  	The width.
	 * @param 		  	height	  	The height.
	 * @param 		  	near_plane	The near plane.
	 * @param 		  	far_plane 	The far plane.
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	ARUNITY_API bool get_projection(float *m, float width, float height, float near_plane, float far_plane);

	/**********************************************************************************************//**
	 * @fn	ARUNITY_API void add_marker(int id, float length);
	 *
	 * @brief	Adds a marker.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/31
	 *
	 * @param	id	  	The identifier.
	 * @param	length	The length.
	 **************************************************************************************************/

	ARUNITY_API void add_marker(int id, float length);

	/**********************************************************************************************//**
	 * @fn	ARUNITY_API bool exist_marker(int id);
	 *
	 * @brief	Exist marker.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/31
	 *
	 * @param	id	The identifier.
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	ARUNITY_API bool exist_marker(int id);

	/**********************************************************************************************//**
	 * @fn	ARUNITY_API bool get_marker_texture(int id, int size, char *filepath);
	 *
	 * @brief	Gets marker texture.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/31
	 *
	 * @param 		  	id			The identifier.
	 * @param 		  	size		The size.
	 * @param [in,out]	filepath	If non-null, the filepath.
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	ARUNITY_API bool get_marker_texture(int id, int size, char *filepath);

	/**********************************************************************************************//**
	 * @fn	ARUNITY_API void set_dictionary(int dict);
	 *
	 * @brief	Sets a dictionary.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/31
	 *
	 * @param	dict	The dictionary.
	 **************************************************************************************************/

	ARUNITY_API void set_dictionary(int dict);

	/**********************************************************************************************//**
	 * @fn	ARUNITY_API int get_dictionary_words(int dict);
	 *
	 * @brief	Gets dictionary words.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/31
	 *
	 * @param	dict	The dictionary.
	 *
	 * @return	The dictionary words.
	 **************************************************************************************************/

	ARUNITY_API int get_dictionary_words();

	/**********************************************************************************************//**
	 * @fn	ARUNITY_API int get_dictionary();
	 *
	 * @brief	Gets the dictionary.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/31
	 *
	 * @return	The dictionary.
	 **************************************************************************************************/

	ARUNITY_API int get_dictionary();

	/**********************************************************************************************//**
	 * @fn	ARUNITY_API bool test_update_camera_frame(unsigned int *buffer);
	 *
	 * @brief	Tests update camera frame.
	 *
	 * @author	liu-wenwu
	 * @date	2016/8/31
	 *
	 * @param	[out]	buffer	If non-null, the buffer.
	 *
	 * @return	true if the test passes, false if the test fails.
	 **************************************************************************************************/

	ARUNITY_API bool test_update_camera_frame(unsigned int *buffer);


}


#endif
