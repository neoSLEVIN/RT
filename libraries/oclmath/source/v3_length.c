/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_length.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 21:44:55 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/06 21:46:00 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ocl_math.h"

cl_float	v3_length(FLT3 v)
{
	return ((cl_float)sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
	//TODO try search for float sqrt
}
