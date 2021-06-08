__kernel void hello_kernel(__global const double *a, 
						   __global const double *b, 
						   __global       double *result)
{
    int gid = get_global_id(0);
    result[gid] = a[gid] + b[gid];
}
