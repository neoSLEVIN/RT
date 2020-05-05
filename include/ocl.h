/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 17:43:40 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/05 08:07:10 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef OCL_H
# define OCL_H

# ifdef __APPLE__
#  include "OpenCL/opencl.h"
# else
#  include "CL/cl.h"
# endif

#include "libft.h"

# define KERNEL_FILE_CNT 1
# define KERNEL_FILE_SIZE 12000

# define ROWS 500
# define COLS 800
# define BYTES_PER_PIXEL 3

typedef struct			s_opencl
{
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	command_queue;
	char				*kernel_text[KERNEL_FILE_CNT];
	size_t				kernel_size[KERNEL_FILE_CNT];
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				mem_obj[2];
	size_t				mem_length;
	cl_int				*mem[2];
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
void					set_params_cl(t_ocl *ocl);
/*
** =================================== Utils ===================================
*/
t_ocl					*new_ocl(void);
void					check_error_cl(const int num, const char *message,
								char *path);

#endif