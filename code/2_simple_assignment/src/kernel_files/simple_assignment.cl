__kernel void simple_assignment(__global const int *a, 
						   __global       int *result)
{
    int gid = get_global_id(0);
    result[gid] = a[gid] + 1;
}
