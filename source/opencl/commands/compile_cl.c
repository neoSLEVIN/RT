/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_cl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 15:44:49 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/05 22:01:36 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

static char	*g_kernel_file_arr[KERNEL_FILE_CNT] = {"kernel/ray_tracing.cl"};

static void	get_kernel_text(char **kernel_text, size_t *kernel_size)
{
	int	i;
	int	fd;
	int	source_size;

	i = -1;
	while (++i < KERNEL_FILE_CNT)
	{
		if ((fd = open(g_kernel_file_arr[i], O_RDONLY)) < 0)
			check_error_cl(fd, "Can't open file", g_kernel_file_arr[i]);
		if (!(kernel_text[i] = ft_strnew(KERNEL_FILE_SIZE)))
			check_error_cl(1, "Can't allocate memory for kernel_text", NULL);
		if ((source_size = read(fd, kernel_text[i], KERNEL_FILE_SIZE)) < 0)
			check_error_cl(source_size, "Can't read file",
				g_kernel_file_arr[i]);
		if (source_size == 0 || source_size >= KERNEL_FILE_SIZE)
			check_error_cl(source_size + 1, "Max size/Empty file",
				g_kernel_file_arr[i]);
		kernel_size[i] = source_size;
		close(fd);
	}
}

void	compile_cl(t_ocl *ocl)
{
	int		err;
	char	*options;
	char	*log_str;
	size_t	log_size;

	options = BUILD_OPTIONS_CL;
	get_kernel_text(ocl->kernel_text, ocl->kernel_size);
	ocl->program = clCreateProgramWithSource(ocl->context, 1,
		(const char **)&ocl->kernel_text, (const size_t *)&ocl->kernel_size, &err);
	check_error_cl(err, "clCreateProgramWithSource", NULL);
	err = clBuildProgram(ocl->program, 1, &ocl->device_id, options, NULL, NULL);
	if (err != CL_SUCCESS)
	{
		clGetProgramBuildInfo(ocl->program, ocl->device_id,
			CL_PROGRAM_BUILD_LOG, 1, NULL, &log_size);
		if (!(log_str = (char*)malloc(log_size)))
			ft_error("Can't allocate memory");
		clGetProgramBuildInfo(ocl->program, ocl->device_id,
			CL_PROGRAM_BUILD_LOG, log_size, log_str, NULL);
		ft_error(log_str);
	}
	ocl->kernel = clCreateKernel(ocl->program, "ray_tracing", &err);
	check_error_cl(err, "clCreateKernel", NULL);
}
