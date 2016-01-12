static const char* invert_gamma_cl_source =
"__kernel void gegl_invert_gamma(__global const float4* in, 	\n"
"								__global float4* out ) 			\n"
"{ 																\n"
"	int id = get_global_id(0); 									\n"
" 																\n"
"	float4 inpixel = in[id]; 									\n"
"	float4 outpixel; 											\n"
"	outpixel.xyz = 1.0 - inpixel.xyz; 							\n"
"	outpixel.w = inpixel.w; 									\n"
" 																\n"
"	out[id] = outpixel; 										\n"
"} 																\n"
"";
