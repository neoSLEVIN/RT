/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_marker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 07:52:50 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/16 07:55:49 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	clear_shape_marker(t_rt *rt)
{
	if (rt->info->s_marker)
	{
		rt->info->s_marker->dto.marker = 0;
		rt->ocl->dto.shapes[rt->info->s_marker->index].marker = 0;
		rt->info->s_marker = NULL;
	}
}

void	clear_light_marker(t_rt *rt)
{
	if (rt->info->l_marker)
	{
		rt->info->l_marker->dto.marker = 0;
		rt->ocl->dto.lights[rt->info->l_marker->index].marker = 0;
		rt->info->l_marker = NULL;
	}
}
