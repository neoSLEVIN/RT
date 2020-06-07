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

_Bool	do_change_shape_param(cl_float *param, SHAPE_TYPE type, int diff)
{
	cl_float	coefficient;

	coefficient = (cl_float)diff * ((cl_float)diff + 0.15f);
	if (type == PLANE)
		return (FALSE);
	else if (type == SPHERE || type == CYLINDER || type == CAPPEDCYLINDER)
	{
		if (*param * coefficient < 0.1f)
			return (FALSE);
		else
			*param *= coefficient;
	}
	else if (type == CONE)
	{
		if (rad_to_deg(*param) + (cl_float)diff * 2 < 1.0f ||
				rad_to_deg(*param) + (cl_float)diff * 2 > 89.0f)
			return (FALSE);
		else
			*param += deg_to_rad(diff * 2);
	}
	else
		ft_error("Unknown type (change_shape_param)");
	return (TRUE);
}

void	change_shape_param(t_rt *rt)
{
	if (!rt->info->s_marker || !rt->info->s_marker->dto)
	{
		rt->info->scroll_cnt = 0;
		return ;
	}
	if (!rt->info->scroll_cnt)
		return ;
	if (do_change_shape_param(&rt->info->s_marker->dto->param,
			rt->info->s_marker->dto->type, rt->info->scroll_cnt))
		update_shapes_flags(&rt->info->update_shapes,
			&rt->info->update_s_param);
	rt->info->scroll_cnt = 0;
}
