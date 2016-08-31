// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ARUnity.h"
#include <windows.h> 


void __stdcall logger(int level, const char* msg)
{
	FILE *out = stdout;
	switch (level)
	{
	case LOG_ERROR:
		out = stderr; break;
	case LOG_WARNING:
	case LOG_INFO:
		out = stdout; break;
	default:
		break;
	};


	SYSTEMTIME sys;
	::GetLocalTime(&sys);
	fprintf(stderr, "%02d:%02d:%02d.%03d %s", sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds, msg);
}

unsigned int buffer[640 * 480];

int __stdcall camera_selector()
{
	int count = get_camera_count();
	printf("camera count:%d\n", count);

	char name[256];
	for (int i = 0; i < count; ++i)
	{
		get_camera_name(i, name, 256);
		printf("[%d] %s\n", i, name);
	}

	return count - 1;
}


void __stdcall proj_callback(float *proj)
{
	printf("\nprojection mat\n");
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			printf("%f,", proj[i * 4 + j]);
		}
		printf("\n");
	}
}


int _tmain(int argc, _TCHAR* argv[])
{

	set_camera_selector(camera_selector);
	register_logger(logger);


	if (!start_camera())
	{
		printf("start failed\n");
		return 1;
	}
	start_algorithm();

	add_marker(2, 0.01);

	int camera_width;
	int camera_height;

	get_camera_size(&camera_width, &camera_height);
	printf("camera size:%d*%d\n", camera_width, camera_height);

	unsigned int *buffer = new unsigned int[camera_width*camera_height];

	unsigned int *tex = new unsigned int[128*128];


	while (test_update_camera_frame(buffer))
	{
		float modelview[16];
		bool tracked = get_marker_pose(2, modelview);


	}

	system("pause");

	return 0;
}

