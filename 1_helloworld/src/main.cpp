/*****************************************************************************
* Filename : main.cpp
* Date : 17-9-2020
* Author : Ram
* Email : ramkalath@gmail.com
 * Breif Description : learning opencl
 * Detailed Description : beginnings of learning opencl - lets start with a helloworld program
*****************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <CL/cl.h>
#include <string.h>

const int ARRAY_SIZE = 1000;

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
	/* =======================================================================================================
	1) creating a context
	======================================================================================================= */
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
	const char* kernel_code = get_program_from_file("./kernel_files/HelloWorld.cl");
	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&kernel_code, NULL, NULL);
	clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    cl_kernel kernel = clCreateKernel(program, "hello_kernel", NULL);

	/* =======================================================================================================
	4) creating data on the host computer
	======================================================================================================= */
    float result[ARRAY_SIZE];
    float a[ARRAY_SIZE];
    float b[ARRAY_SIZE];
    for(unsigned int i=0; i<ARRAY_SIZE; i++)
    {
        a[i] = (float)i;
        b[i] = (float)(i * 2);
    }

	/* =======================================================================================================
	5) creating memory objects for the kernel to use
	======================================================================================================= */
    cl_mem memObjects[3] = {0, 0, 0};
    memObjects[0] = clCreateBuffer(context, CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, sizeof(float) * ARRAY_SIZE, a, NULL);
    memObjects[1] = clCreateBuffer(context, CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, sizeof(float) * ARRAY_SIZE, b, NULL);
    memObjects[2] = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(float) * ARRAY_SIZE, NULL, NULL);
	// in the kernel code arguments 0, 1, 2 maps to the first set of arguments there
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &memObjects[0]);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &memObjects[1]);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &memObjects[2]);

	/* =======================================================================================================
	6) setting worksize info
	======================================================================================================= */
    size_t globalWorkSize[1] = { ARRAY_SIZE };
    size_t localWorkSize[1] = { 1 };
	// This is where the computation happens
    clEnqueueNDRangeKernel(command_queue, 
						   kernel, 
						   1, 
						   NULL, 
						   globalWorkSize, 
						   localWorkSize, 
						   0, 
						   NULL, 
						   NULL);

	/* =======================================================================================================
	7) reading the buffer back to the host
	======================================================================================================= */
    clEnqueueReadBuffer(command_queue, 
						memObjects[2], 
						CL_TRUE, 
						0, 
						ARRAY_SIZE * sizeof(float), 
						result, 
						0, 
						NULL, 
						NULL);

    for(unsigned int i=0; i<ARRAY_SIZE; i++) 
		std::cout << result[i] << " ";

	return 0;
}

