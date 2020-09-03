/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_cl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/16 03:34:49 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

static void	get_kernel_text(char **kernel_text, size_t *kernel_size)
{
	int		i;
	char	*temp;
	char	*for_free;

	i = -1;
	while (++i < KERNEL_FILE_CNT)
	{
		temp = ft_get_text_file(g_kernel_file_arr[i], KERNEL_FILE_SIZE);
		if (!*temp)
			check_error_cl(1, "Empty file", g_kernel_file_arr[i]);
		*kernel_size += ft_strlen(temp);
		for_free = *kernel_text;
		if (!(*kernel_text = ft_strnew(*kernel_size)))
			check_error_cl(1, "Can't allocate memory for kernel_text", NULL);
		if (for_free != NULL)
			ft_strcat(*kernel_text, for_free);
		ft_strdel(&for_free);
		ft_strcat(*kernel_text, temp);
		ft_strdel(&temp);
	}
}

void		compile_cl(t_ocl *ocl)
{
	int		err;
	char	*options;
	char	*log_str;
	size_t	log_size;

	options = BUILD_OPTIONS_CL;
	get_kernel_text(&ocl->kernel_text, &ocl->kernel_size);
	ocl->program = clCreateProgramWithSource(ocl->context, 1,
		(const char **)&ocl->kernel_text, (const size_t *)&ocl->kernel_size,
		&err);
	check_error_cl(err, "clCreateProgramWithSource", NULL);
	ft_strdel(&ocl->kernel_text);
	err = clBuildProgram(ocl->program, 1, &ocl->device, options, NULL, NULL);
	clGetProgramBuildInfo(ocl->program, ocl->device,
		CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
	if (!(log_str = (char*)malloc(log_size)))
		ft_error("Can't allocate memory");
	clGetProgramBuildInfo(ocl->program, ocl->device,
		CL_PROGRAM_BUILD_LOG, log_size, log_str, NULL);
	if (log_str && log_str[0] && log_str[1] && log_str[2])
		ft_putstr(log_str);
	ft_strdel(&log_str);
	check_error_cl(err, "clBuildProgram", NULL);
	ocl->kernel = clCreateKernel(ocl->program, "render_kernel", &err);
	check_error_cl(err, "clCreateKernel", NULL);
}
