/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 20:00:00 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/01 20:49:36 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

const char *kernel_source = "\n" \
	"__kernel void square(__global float* input, __global float* output,\n" \
	"\tconst unsigned int count)\n{\n" \
	"\tint\ti = get_global_id(0);\n" \
	"\n\tif (i < count)\n" \
	"\t\toutput[i] = input[i] * input[i] * input[i];\n" \
	"}\n";

int	main(void)
{
	cl_int				err;
	cl_uint				num_platforms;
	cl_platform_id		first_platform_id;
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	commands;
	cl_program			program;
	cl_mem				buf_a;
	cl_mem				buf_b;
	float	a[3] = {0,1,2};
	float	b[3] = {0,0,0};

	if ((err = clGetPlatformIDs(1, &first_platform_id, &num_platforms)))
		return (printf("Error: %i\tBAD PLATFORM\n", err));
	if ((err = clGetDeviceIDs(first_platform_id, CL_DEVICE_TYPE_GPU, 1,
								&device_id, NULL)))
	{
		printf("Error: %i\tBAD GPU\n", err);
		if ((err = clGetDeviceIDs(first_platform_id, CL_DEVICE_TYPE_CPU, 1,
								&device_id, NULL)))
			return(printf("Error: %i\tBAD CPU\n", err));
	}
	context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &err);
	if (err)
		return(printf("Error: %i\tBAD CONTEXT\n", err));
	commands = clCreateCommandQueue(context, device_id, 0, &err);
	if (err)
		return(printf("Error: %i\tBAD COMMAND\n", err));
	program = clCreateProgramWithSource(context, 1,
							(const char**)&kernel_source, NULL, &err);
	if (err)
		return(printf("Error: %i\tBAD PROGRAM\n", err));
	if ((err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL)))
		return(printf("Error: %i\tBAD BUILD\n", err));
	buf_a = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
						sizeof(float) * 3, a, NULL);
	buf_b = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
						sizeof(float) * 3, NULL, NULL);
	return (0);
}
