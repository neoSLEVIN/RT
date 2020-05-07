/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_kernel_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 21:20:57 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/06 22:06:55 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

void	set_kernel_args(cl_kernel kernel, t_dto *dto)
{
	cl_int	err;

	err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &(dto->input_shapes));
	check_error_cl(err,"clSetKernelArg", "input_shapes");
	err = clSetKernelArg(kernel, 1, sizeof(int), dto->s_cnt);
	check_error_cl(err,"clSetKernelArg", "s_cnt");
	err = clSetKernelArg(kernel, 2, sizeof(cl_mem), &(dto->input_lights));
	check_error_cl(err,"clSetKernelArg", "input_lights");
	err = clSetKernelArg(kernel, 3, sizeof(int), dto->l_cnt);
	check_error_cl(err,"clSetKernelArg", "l_cnt");
	err = clSetKernelArg(kernel, 4, sizeof(DTO_CAM), &(dto->cam));
	check_error_cl(err,"clSetKernelArg", "cam");
	err = clSetKernelArg(kernel, 5, sizeof(cl_mem), &(dto->output_data));
	check_error_cl(err,"clSetKernelArg", "output_data");
	err = clSetKernelArg(kernel, 6, sizeof(cl_mem), &(dto->input_seeds));
	check_error_cl(err,"clSetKernelArg", "input_seeds");
}