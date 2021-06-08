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

int main()
{
	// first get the platform information
	unsigned int platformcount;	
	clGetPlatformIDs(5, NULL, &platformcount);
	cl_platform_id *platforms = (cl_platform_id *)malloc(sizeof(cl_platform_id) * platformcount);
	clGetPlatformIDs(platformcount, platforms, NULL);

	for(unsigned int i=0; i<platformcount; ++i)
	{
		// Each platform has devices. Querying and obtaining all the devices
		unsigned int devicecount;	
		clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &devicecount);
		cl_device_id *devices = (cl_device_id *)malloc(sizeof(cl_device_id) * devicecount);
		clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, devicecount, devices, NULL);
		
		size_t infosize;
		char *info;

		// lets print the properties of each of the devices
		for(unsigned int j=0; j<devicecount; ++j)
		{
			clGetDeviceInfo(devices[j], CL_DEVICE_NAME, 0, NULL, &infosize);
			info = (char *)malloc(sizeof(char) * infosize);
			clGetDeviceInfo(devices[j], CL_DEVICE_NAME, infosize, info, NULL);
			std::cout << info << std::endl;
			delete info;

			size_t *info = reinterpret_cast<size_t *>(info);
			clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_GROUP_SIZE, 0, NULL, &infosize);
			info = (size_t *)malloc(sizeof(size_t) * infosize);
			clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_GROUP_SIZE, infosize, info, NULL);
			std::cout << *info << std::endl;
			delete info;

			clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_ITEM_SIZES, 0, NULL, &infosize);
			info = (size_t *)malloc(sizeof(size_t) * infosize);
			clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_ITEM_SIZES, infosize, info, NULL);
			std::cout << *info << std::endl;

			std::cout << "--------------------------" << std::endl;
		}
	}

	return 0;
}
