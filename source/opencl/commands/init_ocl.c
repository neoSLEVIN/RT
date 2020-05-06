/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ocl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 13:07:11 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/06 04:15:41 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

void	init_ocl(t_ocl *ocl)
{
	ocl->platform = NULL;
	ocl->device = NULL;
	ocl->context = NULL;
	ocl->queue = NULL;
	ocl->kernel_text = NULL;
	ocl->kernel_size = 0;
	ocl->program = NULL;
	ocl->kernel = NULL;
	ocl->work_size = ROWS * COLS;
	ocl->group_size = GROUP_SIZE;
	ocl->dto.shapes = NULL;
	ocl->dto.lights = NULL;
	ocl->dto.input_shapes = NULL;
	ocl->dto.input_lights = NULL;
	ocl->dto.input_seeds = NULL;
	ocl->dto.output_data = NULL;
	ocl->dto.buffer = (cl_float3*)malloc(sizeof(cl_float3) * ocl->work_size);
	if (!ocl->dto.buffer)
		ft_error("Can't allocate memory");
}
