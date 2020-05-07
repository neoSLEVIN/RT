/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_cl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 15:48:36 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/06 21:46:00 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

void	setting_cl(t_ocl *ocl, t_scene *scene)
{
	translate_cam(&ocl->dto.cam, &scene->cam);
	translate_shapes(&ocl->dto.shapes, scene->shapes, scene->s_cnt);
	ocl->dto.s_cnt = &scene->s_cnt;
	translate_lights(&ocl->dto.lights, scene->lights, scene->l_cnt);
	ocl->dto.l_cnt = &scene->l_cnt;
	set_memory_output(ocl);
	set_memory_input(ocl, scene);
	set_kernel_args(ocl->kernel, &ocl->dto);
}