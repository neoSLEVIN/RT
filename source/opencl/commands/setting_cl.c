/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_cl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/21 02:57:09 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

void	setting_cl(t_ocl *ocl, SCENE *scene, t_info *info)
{
	scene->cam.dto = &ocl->dto.cam;
	init_dto_cam(scene->cam.dto, scene->cam.fov, scene->cam.display);
	translate_cam(&ocl->dto.cam, &scene->cam);
	translate_shapes(&ocl->dto.shapes, scene->shapes, scene->s_cnt);
	ocl->dto.s_cnt = &scene->s_cnt;
	translate_lights(&ocl->dto.lights, scene->lights, scene->l_cnt);
	ocl->dto.l_cnt = &scene->l_cnt;
	translate_textures(&ocl->dto.textures, scene->textures, scene->t_cnt);
	ocl->dto.t_cnt = &scene->t_cnt;
	translate_textures(&ocl->dto.normal_maps, scene->normal_maps, scene->n_cnt);
	ocl->dto.n_cnt = &scene->n_cnt;
	ocl->dto.p_cnt = &scene->off.p_cnt;
	ocl->dto.f_cnt = &scene->off.f_cnt;
	translate_off(&ocl->dto, &scene->off);
	ocl->dto.cursor = &info->lmc_current_pos;
	ocl->dto.shape_id = &info->shape_id;
	ocl->dto.anti_aliasing = &scene->anti_aliasing;
	ocl->dto.mirror = &scene->mirror;
	ocl->dto.filter = &scene->filter;
	ocl->dto.filter_params = &scene->filter_params;
	set_memory_output(ocl);
	set_memory_input(ocl, scene);
	set_memory_input_seeds(ocl);
	set_kernel_args(ocl->kernel, &ocl->dto);
}
