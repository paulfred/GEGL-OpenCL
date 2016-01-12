__kernel void gegl_invert_gamma(__global const float4* in,
								__global float4* out )
{
	int id = get_global_id(0);

	float4 inpixel = in[id];
	float4 outpixel;
	outpixel.xyz = 1.0 - inpixel.xyz;
	outpixel.w = inpixel.w;

	out[id] = outpixel;
}
