/**********************************************************************************************//**
 * @file	Common.h
 *
 * @brief	Declares the common definitions.
 **************************************************************************************************/

#ifndef __COMMON_H__
#define __COMMON_H__

/**********************************************************************************************//**
 * @enum	LOG_LEVEL
 *
 * @brief	Values that represent log levels.
 **************************************************************************************************/

enum LOG_LEVEL
{
	LOG_ERROR,
	LOG_WARNING,
	LOG_INFO
};

/**********************************************************************************************//**
 * @typedef	void(__stdcall *LOGCALLBACK)(int level, const char* msg)
 *
 * @brief	Defines an alias representing the log callback.
 **************************************************************************************************/

typedef void(__stdcall *LOGCALLBACK)(int level, const char* msg);

/**********************************************************************************************//**
 * @typedef	int(__stdcall *CAMERA_SELECTOR)()
 *
 * @brief	Defines an alias representing the *camera selector.
 **************************************************************************************************/

typedef int(__stdcall *CAMERA_SELECTOR)();



#endif
