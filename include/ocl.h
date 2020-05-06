/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 17:43:40 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/06 07:29:55 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef OCL_H
# define OCL_H

# ifdef __APPLE__
#  include "OpenCL/opencl.h"
# else
#  include "CL/cl.h"
# endif

# include "libft.h"
# include "scene.h"

# ifdef __APPLE__
# define BUILD_OPTIONS_CL "-cl-std=CL1.0 -cl-mad-enable"
# else
# define BUILD_OPTIONS_CL NULL
# endif

# define ROWS 600
# define COLS 1000
# define GROUP_SIZE 64
# define BYTES_PER_PIXEL 3

# define KERNEL_FILE_SIZE 13000
/*
** TODO !!! Don't forget to add the path of the kernel file in CMakeList !!!
*/
# define KERNEL_FILE_CNT 1
static char	*g_kernel_file_arr[KERNEL_FILE_CNT] = {
		"kernel/ray_tracing2.cl"
};
/*
** TODO !!! Don't forget to add the path of the kernel file in CMakeList !!!
*/
typedef struct			s_dto
{
	DTO_SHAPE			*shapes;
	DTO_LIGHT			*lights;
	cl_mem				input_shapes;
	cl_mem				input_lights;
	cl_mem				input_seeds;
	cl_mem				output_data;
	cl_float3			*buffer;
}						t_dto;

typedef struct			s_opencl
{
	cl_platform_id		platform;
	cl_device_id		device;
	cl_context			context;
	cl_command_queue	queue;
	char				*kernel_text;
	size_t				kernel_size;
	cl_program			program;
	cl_kernel			kernel;
	size_t				work_size;
	size_t				group_size;
	t_dto				dto;
}						t_ocl;

/*
** ================================= Commands ==================================
*/
void					init_ocl(t_ocl *ocl);
void					create_cl(t_ocl *ocl);
void					compile_cl(t_ocl *ocl);
void					run_cl(t_ocl *ocl);
/*
** ================================= Settings ==================================
*/
void					set_params_cl(t_ocl *ocl, t_scene *scene);
/*
** =================================== Utils ===================================
*/
t_ocl					*new_ocl(void);
void					check_error_cl(const int num, const char *message,
								char *path);

#endif
