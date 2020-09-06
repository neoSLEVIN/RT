/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_angle_by_diff.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:28:23 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:28:23 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

FLT2	get_angle_by_diff(INT2 diff, INT2 axis, INT2 screen_size)
{
	return ((FLT2){(cl_float)diff.x / screen_size.x * PI / 4 * axis.x,
					(cl_float)diff.y / screen_size.y * PI / 6 * axis.y});
}
