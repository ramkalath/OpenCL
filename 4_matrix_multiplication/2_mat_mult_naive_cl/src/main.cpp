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
	/* =======================================================================================================
	1) creating a context
	======================================================================================================= */
	// finding out all the platforms on the computer
	unsigned int platformcount;
	clGetPlatformIDs(5, NULL, &platformcount);
	cl_platform_id *platforms = (cl_platform_id *)malloc(sizeof(cl_platform_id)*platformcount);
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
	const char* kernel_code = get_program_from_file("./Kernel_files/matmult1.cl");
	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&kernel_code, NULL, NULL);
	clBuildProgram(program, 0, NULL, NULL, NULL, NULL); // we have omitted build error checks; we need to do that too
    cl_kernel kernel = clCreateKernel(program, "matmult1", NULL);

	/* =======================================================================================================
	4) creating data on the host computer
	======================================================================================================= */
	int M = 3;
	int N = 3;
	int K = 4;
    float A[12] = {5, 2, 6, 1, 0, 6, 2, 0, 3, 8, 1, 4};
    float B[12] = {7, 5, 8, 1, 8, 2, 9, 4, 3, 5, 3, 7};
	float C[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	/* =======================================================================================================
	5) creating memory objects for the kernel to use
	======================================================================================================= */

    cl_mem memObjects[3] = {0, 0, 0};
    memObjects[0] = clCreateBuffer(context, CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, sizeof(float)*12, A, NULL);
    memObjects[1] = clCreateBuffer(context, CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, sizeof(float)*12, B, NULL);
    memObjects[2] = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(float)*9, NULL, NULL);

    clSetKernelArg(kernel, 0, sizeof(int), (void*)&M);
    clSetKernelArg(kernel, 1, sizeof(int), (void*)&N);
    clSetKernelArg(kernel, 2, sizeof(int), (void*)&K);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), &memObjects[0]);
    clSetKernelArg(kernel, 4, sizeof(cl_mem), &memObjects[1]);
    clSetKernelArg(kernel, 5, sizeof(cl_mem), &memObjects[2]);

	/* =======================================================================================================
	6) setting worksize info
	======================================================================================================= */
	size_t globalWorkSize[2] = {(size_t)M, (size_t)N};
    size_t localWorkSize[1] = {1};

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
						memObjects[2], // read from mem object 2
						CL_TRUE, // blocking_read - waits for the read to complete before return
						0, 
						9*sizeof(float), 
						C, // into result
						0, 
						NULL, 
						NULL);


	/* printing the result ================================================================================*/
	for(unsigned int i=0; i<9; i++) 
		std::cout << C[i] << " ";

	std::cout << std::endl;

	return 0;
}
