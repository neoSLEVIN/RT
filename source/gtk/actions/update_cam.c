/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 05:10:50 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/07 05:11:17 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	update_cam(t_rt *rt)
{
	int	err;

	translate_cam(&rt->ocl->dto.cam, &rt->scene->cam);
	err = clSetKernelArg(rt->ocl->kernel, 4, sizeof(DTO_CAM),
						&(rt->ocl->dto.cam));
	check_error_cl(err,"clSetKernelArg", "cam");
}
