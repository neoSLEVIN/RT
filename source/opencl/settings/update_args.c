/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 09:31:44 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/21 03:06:41 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

void	update_filter_params(t_ocl *ocl)
{
	int	err;

	err = clSetKernelArg(ocl->kernel, 12, sizeof(FLT3),
						ocl->dto.filter_params);
	check_error_cl(err, "clSetKernelArg", "filter_params");
}

void	update_cursor_arg(t_ocl *ocl)
{
	int	err;

	err = clSetKernelArg(ocl->kernel, 7, sizeof(INT2), ocl->dto.cursor);
	check_error_cl(err, "clSetKernelArg", "cursor");
}

void	update_cam_arg(t_ocl *ocl, _Bool *update_flag)
{
	int	err;

	err = clSetKernelArg(ocl->kernel, 4, sizeof(DTO_CAM), &ocl->dto.cam);
	check_error_cl(err, "clSetKernelArg", "cam");
	*update_flag = FALSE;
}

void	update_shapes_arg(t_ocl *ocl, _Bool *update_size, _Bool *update_shapes)
{
	int	err;
	int	alloc_size;

	clReleaseMemObject(ocl->dto.input_shapes);
	alloc_size = (*ocl->dto.s_cnt == 0) ? 1 : *ocl->dto.s_cnt;
	ocl->dto.input_shapes = clCreateBuffer(ocl->context,
		CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR,
		sizeof(DTO_SHAPE) * alloc_size, ocl->dto.shapes, &err);
	check_error_cl(err, "clCreateBuffer", "input_shapes");
	err = clSetKernelArg(ocl->kernel, 0, sizeof(cl_mem),
		&(ocl->dto.input_shapes));
	check_error_cl(err, "clSetKernelArg", "input_shapes");
	if (*update_size)
	{
		err = clSetKernelArg(ocl->kernel, 1, sizeof(int), ocl->dto.s_cnt);
		check_error_cl(err, "clSetKernelArg", "s_cnt");
		*update_size = FALSE;
	}
	*update_shapes = FALSE;
}

void	update_lights_arg(t_ocl *ocl, _Bool *update_size, _Bool *update_lights)
{
	int	err;
	int	alloc_size;

	clReleaseMemObject(ocl->dto.input_lights);
	alloc_size = (*ocl->dto.l_cnt == 0) ? 1 : *ocl->dto.l_cnt;
	ocl->dto.input_lights = clCreateBuffer(ocl->context,
		CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR,
		sizeof(DTO_LIGHT) * alloc_size, ocl->dto.lights, &err);
	check_error_cl(err, "clCreateBuffer", "input_lights");
	err = clSetKernelArg(ocl->kernel, 2, sizeof(cl_mem),
						&(ocl->dto.input_lights));
	check_error_cl(err, "clSetKernelArg", "input_lights");
	if (*update_size)
	{
		err = clSetKernelArg(ocl->kernel, 3, sizeof(int), ocl->dto.l_cnt);
		check_error_cl(err, "clSetKernelArg", "l_cnt");
		*update_size = FALSE;
	}
	*update_lights = FALSE;
}
