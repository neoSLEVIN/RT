/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/10 22:29:28 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl_math.h"

/*
** =============================== Angle in RAD ================================
*/

FLT3	v3_rot_x(FLT3 v, cl_float angle)
{
	FLT3	new_v;

	new_v.x = v.x;
	new_v.y = v.y * cos(angle) - v.z * sin(angle);
	new_v.z = v.y * sin(angle) + v.z * cos(angle);
	return (new_v);
}

FLT3	v3_rot_y(FLT3 v, cl_float angle)
{
	FLT3	new_v;

	new_v.x = v.x * cos(angle) + v.z * sin(angle);
	new_v.y = v.y;
	new_v.z = v.z * cos(angle) - v.x * sin(angle);
	return (new_v);
}

FLT3	v3_rot_z(FLT3 v, cl_float angle)
{
	FLT3	new_v;

	new_v.x = v.x * cos(angle) - v.y * sin(angle);
	new_v.y = v.x * sin(angle) + v.y * cos(angle);
	new_v.z = v.z;
	return (new_v);
}

FLT3	v3_rot_v(FLT3 v, FLT3 k, cl_float angle)
{
	FLT3	new_v;

	new_v = v3_add(v, v3_scale(v3_cross(k, v), sin(angle)));
	new_v = v3_add(new_v,
			v3_scale(v3_cross(k, v3_cross(k, v)), (1 - cos(angle))));
	return (new_v);
}
