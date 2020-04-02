__kernel void ray_tracing(__global int *out, __global int *in)
{
	int	gid;

	gid = get_global_id(0);

	out[gid] = in[gid] + gid;
}
