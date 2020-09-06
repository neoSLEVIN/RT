/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:19:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:19:56 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

cl_uint3	get_average_from_sum(cl_uint3 *average_sum, cl_uint count_of_pixels)
{
	cl_uint3	average;

	average.x = average_sum->x / count_of_pixels;
	average.y = average_sum->y / count_of_pixels;
	average.z = average_sum->z / count_of_pixels;
	average.x > 255 ? average.x = 255 : 0;
	average.y > 255 ? average.y = 255 : 0;
	average.z > 255 ? average.z = 255 : 0;
	return (average);
}

void		put_pixel_to_average_sum(cl_uchar4 *pixel, cl_uint3 *average)
{
	average->x += (cl_uint)pixel->x;
	average->y += (cl_uint)pixel->y;
	average->z += (cl_uint)pixel->z;
}

void		put_average_to_pixel(cl_uchar4 *pixel, cl_uint3 *average)
{
	pixel->x = (cl_uchar)average->x;
	pixel->y = (cl_uchar)average->y;
	pixel->z = (cl_uchar)average->z;
}
