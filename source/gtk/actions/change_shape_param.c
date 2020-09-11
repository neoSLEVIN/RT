/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_shape_param.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 23:46:06 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/18 02:08:25 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	change_shape_param(t_rt *rt)
{
	if (!rt->info->s_marker || !rt->info->s_marker->dto)
	{
		rt->info->scroll_cnt = 0;
		return ;
	}
	if (!rt->info->scroll_cnt)
		return ;
	if (do_change_shape_param(&rt->info->s_marker->dto->params,
			rt->info->s_marker->dto->transform.dots,
			rt->info->s_marker->dto->type, rt->info->scroll_cnt) ||
			(rt->info->s_marker->dto->type == OFF &&
				do_change_off_dots(rt->scene->off.points, rt->scene->off.p_cnt,
									rt->info->scroll_cnt)))
	{
		update_flags(&rt->info->update_shapes, &rt->info->update_s_param);
		if (rt->info->s_marker->dto->type == TRIANGLE)
			rt->info->update_s_pos = TRUE;
		else if (rt->info->s_marker->dto->type == OFF)
			rt->info->update_off_points = TRUE;
		else
			rt->info->update_s_main = TRUE;
	}
	rt->info->scroll_cnt = 0;
}
