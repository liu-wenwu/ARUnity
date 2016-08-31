#ifndef __MARKER_H__
#define __MARKER_H__

#include "opencv2/opencv.hpp"
#include "opencv2/aruco.hpp"

/**********************************************************************************************//**
 * @class	Marker
 *
 * @brief	A marker.
 *
 * @author	liu-wenwu
 * @date	2016/8/31
 **************************************************************************************************/

class Marker
{
public:
	Marker(int id, float length);

	int get_id()
	{
		return _id;
	}

	bool save(std::string filepath);


	float length(){
		return _length;
	};
	void set_length(float length){
		_length = length;
	};

	void set_pose(float pose[16])
	{
		assert(pose != NULL);
		memcpy(_pose, pose, sizeof(float)* 16);
	}

	void get_pose(float pose[16])
	{
		assert(pose != NULL);
		memcpy(pose, _pose, sizeof(float)* 16);
	}

	void set_tracked(bool tracked)
	{
		_tracked = tracked;
	}
	bool get_tracked()
	{
		return _tracked;
	}


	static bool get_image(cv::Mat &img, int id, int size, cv::Ptr<cv::aruco::Dictionary> dictionary, int board_bits = 1);



	cv::Vec3d rvec;
	cv::Vec3d tvec;

private:
	cv::aruco::PREDEFINED_DICTIONARY_NAME _dict;
	int _id;
	float _length;//m
	int _size;//pixels
	int _border_bits;

	float _pose[16];
	bool _tracked;


};



#endif
