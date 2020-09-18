/*****************************************************************************
* Filename : main.cpp
* Date : 18-9-2020
* Author : Ram
* Email : ramkalath@gmail.com
* Breif Description : convolution using opencl
* Detailed Description :
*****************************************************************************/
#include<iostream>
#include<fstream>
#include<sstream>
#include<CL/cl.h>
#include<string.h>
#include<typeinfo>

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
	unsigned int numplatforms;
	clGetPlatformIDs(5, NULL, &numplatforms);
	cl_platform_id *platforms = (cl_platform_id *)malloc(sizeof(cl_platform_id) * numplatforms);
	clGetPlatformIDs(numplatforms, platforms, NULL);

	// creating a context
	cl_context_properties contextproperties[] = {CL_CONTEXT_PLATFORM, (cl_context_properties)platforms[0], 0};
	cl_context context = clCreateContextFromType(contextproperties, CL_DEVICE_TYPE_CPU, NULL, NULL, NULL);


	/* =======================================================================================================
	2) creating a command queue
	======================================================================================================= */
	// we need to get device id first
	unsigned int numdevices;
	clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, 0, NULL, &numdevices);
	cl_device_id *devices = (cl_device_id *)malloc(sizeof(cl_device_id) * numdevices);
	clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, numdevices, devices, NULL);
	cl_command_queue command_queue = clCreateCommandQueue(context, devices[0], 0, NULL);

	/* =======================================================================================================
	2) creating kernel from the code and building it during runtime
	======================================================================================================= */
	const char* kernel_code = get_program_from_file("./kernel_files/convolution.cl");
	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&kernel_code, NULL, NULL);
	clBuildProgram(program, 0, NULL, NULL, NULL, NULL); // we have omitted build error checks; we need to do that too
    cl_kernel kernel = clCreateKernel(program, "convolve", NULL);

	/* =======================================================================================================
	4) creating data on the host computer
	======================================================================================================= */
	unsigned int inputsignal[8][8] = {
		{3, 1, 1, 4, 8, 2, 1, 3},
		{4, 2, 1, 1, 2, 1, 2, 3},
		{4, 4, 4, 4, 3, 2, 2, 2},
		{9, 8, 3, 8, 9, 0, 0, 0},
		{9, 3, 3, 9, 0, 0, 0, 0},
		{0, 9, 0, 8, 0, 0, 0, 0},
		{3, 0, 8, 8, 9, 4, 4, 4},
		{5, 9, 8, 1, 8, 1, 1, 1}
	};


	unsigned int outputsignal[6][6] = { };

	for(unsigned int i=0; i<8; i++)
	{
		for(unsigned int j=0; j<8; j++)
			std::cout << outputsignal[i][j] << " ";
		std::cout << std::endl;
	}
	unsigned int mask[3][3] = {
		{1, 1, 1},
		{1, 0, 1},
		{1, 1, 1}
	};

	cl_mem inputSignalBuffer = clCreateBuffer(context, 
											  CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, 
											  sizeof(unsigned int)*8*8, 
											  static_cast<void *>(inputsignal), 
											  NULL);
	cl_mem maskBuffer = clCreateBuffer(context, 
									   CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, 
									   sizeof(unsigned int)*8*8, 
									   static_cast<void *>(mask), 
									   NULL);
	cl_mem outputSignalBuffer = clCreateBuffer(context, 
											   CL_MEM_WRITE_ONLY,
											   sizeof(unsigned int)*6*6, 
											   NULL, 
											   NULL);
	unsigned int inputSignalWidth = 8;
	unsigned int maskWidth = 3;

	/* =======================================================================================================
	5) creating memory objects for the kernel to use
	======================================================================================================= */
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputSignalBuffer);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &maskBuffer);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputSignalBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &inputSignalWidth);
    clSetKernelArg(kernel, 4, sizeof(unsigned int), &maskWidth);

	/* =======================================================================================================
	6) setting worksize info
	======================================================================================================= */
    const size_t globalWorkSize[1] = {6*6};
    const size_t localWorkSize[1] = {1};
	
    clock_t start, end; 
    start = clock(); 

	// This is where the computation happens; the enqueue command queues up the command in the command_queue. Later when the previous event is finished, this is executed.
    clEnqueueNDRangeKernel(command_queue, 
						   kernel, 
						   1, 
						   NULL, 
						   globalWorkSize, 
						   localWorkSize, 
						   0, 
						   NULL, 
						   NULL);

	end = clock(); 
	//std::cout << "Time taken by program is : " << double(end - start)/(double)(CLOCKS_PER_SEC) << std::endl;

	/* =======================================================================================================
	7) reading the buffer back to the host
	======================================================================================================= */
    clEnqueueReadBuffer(command_queue, 
						outputSignalBuffer, // read from mem object 2
						CL_TRUE, // blocking_read - waits for the read to complete before return
						0, 
						sizeof(unsigned int) *6*6, 
						outputsignal, // into result
						0, 
						NULL, 
						NULL);



	//for (unsigned int j=0; j<6; j++)
	//{
		//for (unsigned int i=0; i<6; i++)
			//std::cout << outputsignal[i][j] << " ";
		//std::cout << std::endl;
	//}

    //std::cout << std::endl << "Executed program succesfully." << std::endl;
	return 0;
}
