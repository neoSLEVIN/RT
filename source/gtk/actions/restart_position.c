/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart_position.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:22:26 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:22:27 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	restart_position(t_rt *rt)
{
	if (!rt->info->r_key)
		return ;
	translate_cam(&rt->ocl->dto.cam, &rt->scene->cam);
	clear_shape_marker(rt);
	rt->info->update_cam = TRUE;
}
