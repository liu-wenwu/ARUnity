#include "Common.h"
#include "Logger.h"

#include <cstdarg>
#include <cstdio>

 LOGCALLBACK Logger::gLoggerFunc=nullptr;

Logger::Logger()
{
}


Logger::~Logger()
{
}


void Logger::log_format(LOG_LEVEL level, const char * fmt, ...)
{
	if (!gLoggerFunc)
		return;

	char buffer[512];
	int ret;
	va_list args;

	va_start(args, fmt);
	ret = vsprintf(buffer, fmt, args);
	va_end(args);
	gLoggerFunc(level, buffer);
}