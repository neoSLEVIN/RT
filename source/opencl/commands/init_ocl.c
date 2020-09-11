/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ocl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/21 01:09:29 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

void		init_dto_cam(DTO_CAM *cam, cl_float fov, INT2 screen)
{
	cl_float	ratio;

	cam->max_screen = (INT2){COLS, ROWS};
	cam->screen_h = screen.y;
	cam->screen_w = screen.x;
	cam->diff_screen.x = (cam->max_screen.x - cam->screen_w) / 2;
	cam->diff_screen.y = (cam->max_screen.y - cam->screen_h) / 2;
	ratio = (float)cam->screen_w / (float)cam->screen_h;
	cam->viewport_h = tan((double)(fov * RAD / 2));
	cam->viewport_w = cam->viewport_h * ratio;
}

static void	init_off(t_dto *dto)
{
	dto->points = NULL;
	dto->faces = NULL;
	dto->colors = NULL;
	dto->p_cnt = NULL;
	dto->f_cnt = NULL;
	dto->input_points = NULL;
	dto->input_faces = NULL;
	dto->input_colors = NULL;
}

static void	init_dto(t_dto *dto, const size_t work_size)
{
	init_dto_cam(&dto->cam, 25.0f, (INT2){COLS, ROWS});
	dto->textures = NULL;
	dto->normal_maps = NULL;
	dto->shapes = NULL;
	dto->lights = NULL;
	dto->t_cnt = NULL;
	dto->s_cnt = NULL;
	dto->l_cnt = NULL;
	dto->cursor = NULL;
	dto->input_shapes = NULL;
	dto->input_lights = NULL;
	dto->input_seeds = NULL;
	dto->input_texture = NULL;
	dto->input_normal_maps = NULL;
	init_off(dto);
	dto->output_data = NULL;
	dto->output_id = NULL;
	dto->shape_id = NULL;
	dto->anti_aliasing = NULL;
	dto->mirror = NULL;
	dto->buffer = (cl_uchar4*)malloc(sizeof(cl_uchar4) * work_size);
	(!dto->buffer) ? ft_error("Can't allocate memory") : 0;
	dto->filter_buff = (cl_uchar4*)malloc(sizeof(cl_uchar4) * work_size);
	if (!dto->filter_buff)
		ft_error("Can't allocate memory");
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
	init_dto(&ocl->dto, ocl->work_size);
}
