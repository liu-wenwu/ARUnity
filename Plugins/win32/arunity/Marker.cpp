#include "Marker.h"
#include "Logger.h"


Marker::Marker(int id, float length) :
	_dict(cv::aruco::DICT_7X7_1000),
	_id(id),
	_length(length),
	_size(300),
	_border_bits(1),
	_tracked(false)
{

}

bool Marker::get_image(cv::Mat &img, int id, int size, cv::Ptr<cv::aruco::Dictionary> dictionary, int board_bits)
{
	cv::aruco::drawMarker(dictionary, id, size, img, board_bits);
	return true;
}