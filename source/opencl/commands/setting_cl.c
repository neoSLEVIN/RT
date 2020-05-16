/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_cl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/16 07:23:42 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

void	setting_cl(t_ocl *ocl, SCENE *scene, t_info *info)
{
	translate_cam(&ocl->dto.cam, &scene->cam);
	translate_shapes(&ocl->dto.shapes, scene->shapes, scene->s_cnt);
	ocl->dto.s_cnt = &scene->s_cnt;
	translate_lights(&ocl->dto.lights, scene->lights, scene->l_cnt);
	ocl->dto.l_cnt = &scene->l_cnt;
	ocl->dto.cursor = &info->lmc_current_pos;
	ocl->dto.shape_id = &info->shape_id;
	set_memory_output(ocl);
	set_memory_input(ocl, scene);
	set_kernel_args(ocl->kernel, &ocl->dto);
}
