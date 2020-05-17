/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 09:31:44 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/17 00:55:12 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

void	update_cursor_arg(t_ocl *ocl)
{
	int	err;

	err = clSetKernelArg(ocl->kernel, 7, sizeof(INT2), ocl->dto.cursor);
	check_error_cl(err,"clSetKernelArg", "cursor");
}

void	update_cam_arg(t_ocl *ocl, _Bool *update_flag)
{
	int	err;

	err = clSetKernelArg(ocl->kernel, 4, sizeof(DTO_CAM), &ocl->dto.cam);
	check_error_cl(err,"clSetKernelArg", "cam");
	*update_flag = FALSE;
}

void	update_shapes_arg(t_ocl *ocl, _Bool *update_size, _Bool *update_shapes)
{
	int	err;

	clReleaseMemObject(ocl->dto.input_shapes);
	ocl->dto.input_shapes = clCreateBuffer(ocl->context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(DTO_SHAPE) * *ocl->dto.s_cnt, ocl->dto.shapes, &err);
	check_error_cl(err,"clCreateBuffer", "input_shapes");
	err = clSetKernelArg(ocl->kernel, 0, sizeof(cl_mem),
		&(ocl->dto.input_shapes));
	check_error_cl(err,"clSetKernelArg", "input_shapes");
	if (*update_size)
	{
		err = clSetKernelArg(ocl->kernel, 1, sizeof(int), ocl->dto.s_cnt);
		check_error_cl(err,"clSetKernelArg", "s_cnt");
		*update_size = FALSE;
	}
	*update_shapes = FALSE;
}
