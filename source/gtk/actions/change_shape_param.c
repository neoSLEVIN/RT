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

static _Bool	do_change_shape_radius(cl_float *radius, cl_float coefficient)
{
	if (*radius < 0.1f)
		*radius = 0.1f;
	else if (*radius * coefficient < 0.1f)
		return (FALSE);
	else
		*radius *= coefficient;
	return (TRUE);
}

static _Bool	do_change_shape_angle(cl_float *angle, cl_float diff)
{
	if (rad_to_deg(*angle) < 1.0f)
		*angle = deg_to_rad(1.0f);
	else if (rad_to_deg(*angle) > 89.0f)
		*angle = deg_to_rad(89.0f);
	else if (rad_to_deg(*angle) + (cl_float)diff * 2 < 1.0f ||
			rad_to_deg(*angle) + (cl_float)diff * 2 > 89.0f)
		return (FALSE);
	else
		*angle += deg_to_rad(diff * 2);
	return (TRUE);
}

_Bool			do_change_shape_param(FLT3 *params, SHAPE_TYPE type, int diff)
{
	cl_float	coefficient;
	_Bool		do_change;

	do_change = FALSE;
	coefficient = (cl_float)diff * ((cl_float)diff + 0.15f);
	if (type == PLANE)
		return (FALSE);
	else if (type == SPHERE || type == CYLINDER)
		return (do_change_shape_radius(&params->x, coefficient));
	else if (type == CONE)
		return (do_change_shape_angle(&params->x, diff));
	else if (type == CAPPEDCYLINDER)
	{
		if (do_change_shape_radius(&params->x, coefficient))
			do_change = TRUE;
		if (do_change_shape_radius(&params->y, coefficient))
			do_change = TRUE;
		return (do_change);
	}
	else
		ft_error("Unknown type (change_shape_param)");
	return (TRUE);
}

void			change_shape_param(t_rt *rt)
{
	if (!rt->info->s_marker || !rt->info->s_marker->dto)
	{
		rt->info->scroll_cnt = 0;
		return ;
	}
	if (!rt->info->scroll_cnt)
		return ;
	if (do_change_shape_param(&rt->info->s_marker->dto->params,
			rt->info->s_marker->dto->type, rt->info->scroll_cnt))
	{
		update_flags(&rt->info->update_shapes, &rt->info->update_s_param);
		rt->info->update_s_main = TRUE;
	}
	rt->info->scroll_cnt = 0;
}
