__kernel void hello_kernel( const float alpha,
							__global float *a, 
						    __global float *b, 
						    __global float *result)
{
    int gid = get_global_id(0);
    result[gid] = alpha * a[gid] + b[gid];
}
