/*****************************************************************************
* Filename : main.cpp
* Date : 17-9-2020
* Author : Ram
* Email : ramkalath@gmail.com
* Breif Description :
* Detailed Description :
*****************************************************************************/
#include<iostream>
#include<CL/cl.h>

void queryPlatformInfo(cl_platform_id platform, cl_platform_info infotype)
{
	size_t infosize;
	clGetPlatformInfo(platform, infotype, 0, NULL, &infosize);
	char *info = (char *)malloc(sizeof(char) * infosize);
	clGetPlatformInfo(platform, infotype, infosize, info, NULL);
	std::cout << info << std::endl;
}

int main()
{
	// querying and obtaining all the platforms
	unsigned int platformcount;	
	clGetPlatformIDs(5, NULL, &platformcount);
	cl_platform_id *platforms = (cl_platform_id *)malloc(sizeof(cl_platform_id) * platformcount);
	clGetPlatformIDs(platformcount, platforms, NULL);

	// lets print the properties of each of the platforms
	for(unsigned int i=0; i<platformcount; ++i)
	{
		queryPlatformInfo(platforms[i], CL_PLATFORM_NAME);
		queryPlatformInfo(platforms[i], CL_PLATFORM_PROFILE);
		queryPlatformInfo(platforms[i], CL_PLATFORM_VERSION);
		queryPlatformInfo(platforms[i], CL_PLATFORM_VENDOR);
		queryPlatformInfo(platforms[i], CL_PLATFORM_EXTENSIONS);
		std::cout << "--------------------------" << std::endl;
	}

	return 0;
}
