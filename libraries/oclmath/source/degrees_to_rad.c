/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   degrees_to_rad.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 20:47:30 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/06 20:47:30 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ocl_math.h"

cl_float	degrees_to_rad(cl_float angle_in_degrees)
{
	return (angle_in_degrees * PI / 180.0 / 2);
	// TODO why there delimiter 2
}
