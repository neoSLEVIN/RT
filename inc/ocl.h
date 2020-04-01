/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 17:43:40 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/01 03:49:43 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef OCL_H
# define OCL_H

# include "libft.h"

# ifdef __APPLE__
#  include "OpenCL/opencl.h"
# else
#  include "CL/cl.h"
# endif

# define KERNEL_PATH "vector_add.cl"
# define KERNEL_SIZE 10000
# define GLOBAL_WORK_SIZE 10

typedef struct			s_opencl
{
	cl_uint				ret_num_platforms;
	cl_uint				ret_num_devices;
	cl_platform_id		platform_id;
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	command_queue;
	char				*kernel_text;
	size_t				kernel_size;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				mem_obj;
	int					mem_length;
	cl_int*				mem;
}						t_ocl;

void					init_ocl(t_ocl *ocl);
void					create_cl(t_ocl *ocl);
void					compile_cl(t_ocl *ocl);
void					setting_cl(t_ocl *ocl);
void					run_cl(t_ocl *ocl);

#endif
