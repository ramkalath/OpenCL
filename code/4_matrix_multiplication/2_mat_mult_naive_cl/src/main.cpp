/*****************************************************************************
* Filename : main.cpp
* Date : 20-11-2020
* Author : Ram
* Email : ramkalath@gmail.com
* Breif Description : TODO(ram): not yet working!!!
* Detailed Description :
*****************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <CL/cl.h>
#include <string.h>

char* get_program_from_file(const char* file_path)
{
	std::ifstream f(file_path);

	// read all the contents of that file
	std::stringstream f_stream;
	f_stream << f.rdbuf();

	// copy the data to a memory in the heap so that after the scope of this function runs out it still remains
	char* code = (char *)malloc(f_stream.str().length()+1);
	memcpy(code, f_stream.str().c_str(), f_stream.str().length()+1);

	// lets close the open files
	f.close();

	return code;
}

int main()
{
	/* Creating a context */
	// finding out all the platforms on the computer
	unsigned int platformcount;
	clGetPlatformIDs(5, NULL, &platformcount);
	cl_platform_id *platforms = (cl_platform_id *)malloc(sizeof(cl_platform_id) * platformcount);
	clGetPlatformIDs(platformcount, platforms, NULL);

	// creating the context
	cl_context_properties contextproperties[] = {CL_CONTEXT_PLATFORM, (cl_context_properties)platforms[0], 0};
	cl_context context = clCreateContextFromType(contextproperties, CL_DEVICE_TYPE_GPU, NULL, NULL, NULL);

	/* =======================================================================================================
	2) creating a command queue
	======================================================================================================= */
	// we need to get device id first
	unsigned int deviceCount;
	clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, 0, NULL, &deviceCount);
	cl_device_id *devices = (cl_device_id *)malloc(sizeof(cl_device_id) * deviceCount);
	clGetDeviceIDs(platforms[0],  CL_DEVICE_TYPE_ALL, deviceCount, devices, NULL);
	cl_command_queue command_queue = clCreateCommandQueue(context, devices[0], 0, NULL);

	/* =======================================================================================================
	3) creating a kernel from the code; building it during runtime
	======================================================================================================= */
	//TODO(ram):  yet to learn how kernel code works
	const char* kernel_code = get_program_from_file("./kernel_files/matmult1.cl");
	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&kernel_code, NULL, NULL);
	clBuildProgram(program, 0, NULL, NULL, NULL, NULL); // we have omitted build error checks; we need to do that too
    cl_kernel kernel = clCreateKernel(program, "matmult1", NULL);

	/* =======================================================================================================
	4) creating data on the host computer
	======================================================================================================= */


	return 0;
}
