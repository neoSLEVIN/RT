/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_args2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amace-ty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 15:01:01 by amace-ty          #+#    #+#             */
/*   Updated: 2020/09/11 15:01:02 by amace-ty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

void	update_anti_aliasing_arg(t_ocl *ocl)
{
	int	err;

	err = clSetKernelArg(ocl->kernel, 13, sizeof(int),
						ocl->dto.anti_aliasing);
	check_error_cl(err, "clSetKernelArg", "anti_aliasing");
}

void	update_mirror_arg(t_ocl *ocl)
{
	int	err;
	int	mirror;

	mirror = (IS_APPLE) ? 1 : *ocl->dto.mirror;
	err = clSetKernelArg(ocl->kernel, 14, sizeof(int),
						&mirror);
	check_error_cl(err, "clSetKernelArg", "mirror");
}

void	update_off_points_arg(t_ocl *ocl, _Bool *update_points)
{
	int	err;
	int	alloc_size;

	clReleaseMemObject(ocl->dto.input_points);
	alloc_size = (*ocl->dto.p_cnt == 0) ? 1 : *ocl->dto.p_cnt;
	ocl->dto.input_points = clCreateBuffer(ocl->context,
		CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR,
		sizeof(FLT3) * alloc_size, ocl->dto.points, &err);
	check_error_cl(err, "clCreateBuffer", "input_points");
	err = clSetKernelArg(ocl->kernel, 15, sizeof(cl_mem),
						&(ocl->dto.input_points));
	check_error_cl(err, "clSetKernelArg", "input_points");
	*update_points = FALSE;
}
