/*****************************************************************************
* Filename : main.cpp
* Date : 20-11-2020
* Author : Ram
* Email : ramkalath@gmail.com
* Breif Description :
* Detailed Description :
*****************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <CL/cl.h>
#include <string.h>

int main()
{
	/* =======================================================================================================
	1) creating a context
	======================================================================================================= */
	// finding out all the platforms on the computer
	unsigned int platformcount;
	clGetPlatformIDs(5, NULL, &platformcount);
	cl_platform_id *platforms = (cl_platform_id *)malloc(sizeof(cl_platform_id)*platformcount);
	clGetPlatformIDs(platformcount, platforms, NULL);

	// creating the context
	cl_context_properties context_properties[] = {CL_CONTEXT_PLATFORM}
	return 0;
}
