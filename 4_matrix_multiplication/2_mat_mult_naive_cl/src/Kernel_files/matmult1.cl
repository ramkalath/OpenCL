// Kernal for naive 1 mat mult using OpenCL
// Author: Ramkumar N
// Date: 07/12/2020

__kernel void matmult1(const int M, // column size
					   const int N, // row size
					   const int K, 
					   __global const float *A,
					   __global const float *B,
					   __global float *C)
{
	const int gid_row = get_global_id(0); // goes from 0 to M
	const int gid_col = get_global_id(1); // goes from 0 to N
	// notice (gid_row, gid_col) are the row, col of C

	/*float acc = 0.0f;*/
	/*for(int k=0; k<K, k++)*/
	/*{*/
		/*acc += A[gid_row*K+k] + B[k*N+gid_col];*/
		/*acc = 1.0f;*/
		/*acc += A[gid_row*K+k] + B[k*N+gid_col]*/
	/*}*/
	C[gid_row+M*gid_col] = 1.0f;
}
