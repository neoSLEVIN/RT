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

_Bool	do_change_shape_param(FLT3 *params, SHAPE_TYPE type, int diff)
{
	cl_float	coefficient;
	int			without_changes;

	without_changes = 0;
	coefficient = (cl_float)diff * ((cl_float)diff + 0.15f);
	if (type == PLANE)
		return (FALSE);
	else if (type == SPHERE || type == CYLINDER)
	{
		if (params->x < 0.1f)
			params->x = 0.1f;
		else if (params->x * coefficient < 0.1f)
			return (FALSE);
		else
			params->x *= coefficient;
	}
	else if (type == CONE)
	{
		if (rad_to_deg(params->x) < 1.0f)
			params->x = deg_to_rad(1.0f);
		else if (rad_to_deg(params->x) > 89.0f)
			params->x = deg_to_rad(89.0f);
		else if (rad_to_deg(params->x) + (cl_float)diff * 2 < 1.0f ||
				rad_to_deg(params->x) + (cl_float)diff * 2 > 89.0f)
			return (FALSE);
		else
			params->x += deg_to_rad(diff * 2);
	}
	else if (type == CAPPEDCYLINDER)
	{
		if (params->x < 0.1f)
			params->x = 0.1f;
		else if (params->x * coefficient < 0.1f)
			++without_changes;
		else
			params->x *= coefficient;
		if (params->y < 0.1f)
			params->y = 0.1f;
		else if (params->y * coefficient < 0.1f)
			++without_changes;
		else
			params->y *= coefficient;
		return (without_changes == 2 ? FALSE : TRUE);
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
	if (do_change_shape_param(&rt->info->s_marker->dto->params,
			rt->info->s_marker->dto->type, rt->info->scroll_cnt))
	{
		update_flags(&rt->info->update_shapes, &rt->info->update_s_param);
		rt->info->update_s_main = TRUE;
	}
	rt->info->scroll_cnt = 0;
}
