/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_change_shape_param.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 23:15:59 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 23:16:00 by cschoen          ###   ########.fr       */
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

static _Bool	do_change_triangle_dots(FLT3 *dots, cl_float coefficient)
{
	FLT3	new_distance;
	FLT3	center;
	int		i;
	_Bool	do_change;

	do_change = FALSE;
	center = v3_scale(v3_add(v3_add(dots[0], dots[1]), dots[2]), 1.0f / 3.0f);
	i = -1;
	while (++i < 3)
	{
		new_distance = v3_scale(v3_sub(dots[i], center), coefficient);
		if (v3_length(new_distance) < 0.1f && coefficient < 1.0f)
			continue ;
		do_change = TRUE;
		dots[i] = v3_add(center, new_distance);
	}
	return (do_change);
}

static _Bool	do_change_shape_param_norminette(FLT3 *params, FLT3 *dots,
											SHAPE_TYPE type, cl_float coeff)
{
	_Bool	do_change;

	if (type == CAPPEDCONE)
	{
		(do_change_shape_angle(&params->x, coeff)) ? do_change = TRUE : 0;
		(do_change_shape_radius(&params->y, coeff)) ? do_change = TRUE : 0;
		return (do_change);
	}
	else if (type == TRIANGLE)
		return (do_change_triangle_dots(dots, coeff));
	else
		ft_error("Unknown type (change_shape_param)");
	return (TRUE);
}

_Bool			do_change_shape_param(FLT3 *params, FLT3 *dots, SHAPE_TYPE type,
									int diff)
{
	cl_float	coeff;
	_Bool		do_change;

	do_change = FALSE;
	coeff = (cl_float)diff * ((cl_float)diff + 0.15f);
	if (type == PLANE || type == OFF)
		return (FALSE);
	else if (type == SPHERE || type == CYLINDER || type == CIRCLE)
		return (do_change_shape_radius(&params->x, coeff));
	else if (type == CONE)
		return (do_change_shape_angle(&params->x, diff));
	else if (type == CAPPEDCYLINDER || type == CAPPEDPLANE || type == BOX ||
			type == CAPSULE)
	{
		(do_change_shape_radius(&params->x, coeff)) ? do_change = TRUE : 0;
		(do_change_shape_radius(&params->y, coeff)) ? do_change = TRUE : 0;
		if (type == BOX)
			(do_change_shape_radius(&params->z, coeff)) ? do_change = TRUE : 0;
		return (do_change);
	}
	return (do_change_shape_param_norminette(params, dots, type, coeff));
}
