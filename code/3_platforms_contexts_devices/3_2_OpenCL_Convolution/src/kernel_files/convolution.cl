__kernel void convolve(const __global uint * const input,
						__constant uint * const mask,
						__global uint * const output,
						const int inputWidth,
						const int maskWidth)
{
	const int x = get_global_id(0);
	const int y = get_global_id(1);

	uint sum = 0;
	for(unsigned int i=0; i<maskWidth; i++)
	{
		const int idxIntmp = (y+i) * inputWidth + x;
		for(unsigned int j=0; j<maskWidth; j++)
			sum += mask[(i*maskWidth)+j] * input[idxIntmp+j];
	}
	output[y * get_global_size(0) + x] = sum;
}

