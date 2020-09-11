/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_kernel_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/20 22:21:02 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

static void	set_kernel_args2(cl_kernel kernel, t_dto *dto)
{
	cl_int	err;
	int		mirror;

	mirror = (IS_APPLE) ? 1 : *dto->mirror;
	err = clSetKernelArg(kernel, 11, sizeof(cl_mem), &dto->output_id);
	check_error_cl(err, "clSetKernelArg", "output_id");
	err = clSetKernelArg(kernel, 12, sizeof(FLT3), dto->filter_params);
	check_error_cl(err, "clSetKernelArg", "filter_params");
	err = clSetKernelArg(kernel, 13, sizeof(int), dto->anti_aliasing);
	check_error_cl(err, "clSetKernelArg", "anti_aliasing");
	err = clSetKernelArg(kernel, 14, sizeof(int), &mirror);
	check_error_cl(err, "clSetKernelArg", "mirror");
	err = clSetKernelArg(kernel, 15, sizeof(cl_mem), &dto->input_points);
	check_error_cl(err, "clSetKernelArg", "input_points");
	err = clSetKernelArg(kernel, 16, sizeof(cl_mem), &dto->input_faces);
	check_error_cl(err, "clSetKernelArg", "input_faces");
	err = clSetKernelArg(kernel, 17, sizeof(cl_mem), &dto->input_colors);
	check_error_cl(err, "clSetKernelArg", "input_colors");
	err = clSetKernelArg(kernel, 18, sizeof(int), dto->p_cnt);
	check_error_cl(err, "clSetKernelArg", "p_cnt");
	err = clSetKernelArg(kernel, 19, sizeof(int), dto->f_cnt);
	check_error_cl(err, "clSetKernelArg", "f_cnt");
}

void		set_kernel_args(cl_kernel kernel, t_dto *dto)
{
	cl_int	err;

	err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &(dto->input_shapes));
	check_error_cl(err, "clSetKernelArg", "input_shapes");
	err = clSetKernelArg(kernel, 1, sizeof(int), dto->s_cnt);
	check_error_cl(err, "clSetKernelArg", "s_cnt");
	err = clSetKernelArg(kernel, 2, sizeof(cl_mem), &(dto->input_lights));
	check_error_cl(err, "clSetKernelArg", "input_lights");
	err = clSetKernelArg(kernel, 3, sizeof(int), dto->l_cnt);
	check_error_cl(err, "clSetKernelArg", "l_cnt");
	err = clSetKernelArg(kernel, 4, sizeof(DTO_CAM), &(dto->cam));
	check_error_cl(err, "clSetKernelArg", "cam");
	err = clSetKernelArg(kernel, 5, sizeof(cl_mem), &(dto->output_data));
	check_error_cl(err, "clSetKernelArg", "output_data");
	err = clSetKernelArg(kernel, 6, sizeof(cl_mem), &(dto->input_seeds));
	check_error_cl(err, "clSetKernelArg", "input_seeds");
	err = clSetKernelArg(kernel, 7, sizeof(INT2), dto->cursor);
	check_error_cl(err, "clSetKernelArg", "cursor");
	err = clSetKernelArg(kernel, 8, sizeof(cl_mem), &dto->input_texture);
	check_error_cl(err, "clSetKernelArg", "input_texture");
	err = clSetKernelArg(kernel, 9, sizeof(cl_mem), &dto->input_normal_maps);
	check_error_cl(err, "clSetKernelArg", "input_normal_maps");
	err = clSetKernelArg(kernel, 10, sizeof(FILTER), dto->filter);
	check_error_cl(err, "clSetKernelArg", "filter");
	set_kernel_args2(kernel, dto);
}
