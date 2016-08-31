#pragma once


#include "Common.h"



#define LOG_E(format, ...) Logger::log_format(LOG_ERROR,format, __VA_ARGS__)
#define LOG_W(format, ...) Logger::log_format(LOG_WARNING,format, __VA_ARGS__)
#define LOG_I(format, ...) Logger::log_format(LOG_INFO,format, __VA_ARGS__)

/**********************************************************************************************//**
 * @class	Logger
 *
 * @brief	A logger.
 *
 * @author	liu-wenwu
 * @date	2016/8/31
 **************************************************************************************************/

class Logger
{
public:
	Logger();
	~Logger();

	static void set_callback(LOGCALLBACK callback)
	{
		gLoggerFunc = callback;
	}

	static void log_format(LOG_LEVEL level, const char * fmt, ...);


private:
	static LOGCALLBACK gLoggerFunc;

};

