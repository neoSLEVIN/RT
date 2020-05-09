/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ocl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 13:07:11 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/06 21:29:18 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

static void	init_dto_cam(DTO_CAM *cam)
{
	cl_float	fov;
	cl_float	ratio;

	cam->screen_h = ROWS;
	cam->screen_w = COLS;
	fov = 25.0f * PI / 180;
	ratio = (float)cam->screen_w / (float)cam->screen_h;
	cam->viewport_h = tan(fov) / 2;
	cam->viewport_w = cam->viewport_h * ratio;
}

void		init_ocl(t_ocl *ocl)
{
	ocl->platform = NULL;
	ocl->device = NULL;
	ocl->context = NULL;
	ocl->queue = NULL;
	ocl->kernel_text = NULL;
	ocl->kernel_size = 0;
	ocl->work_size = ROWS * COLS;
	ocl->group_size = GROUP_SIZE;
	ocl->program = NULL;
	ocl->kernel = NULL;
	init_dto_cam(&ocl->dto.cam);
	ocl->dto.shapes = NULL;
	ocl->dto.lights = NULL;
	ocl->dto.s_cnt = NULL;
	ocl->dto.l_cnt = NULL;
	ocl->dto.input_shapes = NULL;
	ocl->dto.input_lights = NULL;
	ocl->dto.input_seeds = NULL;
	ocl->dto.output_data = NULL;
	ocl->dto.buffer = (cl_char4*)malloc(sizeof(cl_char4) * ocl->work_size);
	if (!ocl->dto.buffer)
		ft_error("Can't allocate memory");
}
