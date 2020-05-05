/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_cl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 15:44:49 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/04 20:58:03 by cschoen          ###   ########lyon.fr   */
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
	int	ret;

	get_kernel_text(ocl->kernel_text, ocl->kernel_size);
	ocl->program = clCreateProgramWithSource(ocl->context, 1,
		(const char **)&ocl->kernel_text, (const size_t *)&ocl->kernel_size, &ret);
	check_error_cl(ret, "clCreateProgramWithSource", NULL);
	ret = clBuildProgram(ocl->program, 1, &ocl->device_id, NULL, NULL, NULL);
	check_error_cl(ret, "clBuildProgram", NULL);
	ocl->kernel = clCreateKernel(ocl->program, "ray_tracing", &ret);
	check_error_cl(ret, "clCreateKernel", NULL);
}
