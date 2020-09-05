/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:20:33 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:20:35 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static cl_uchar	calc_r(const int matrix[9], int i, t_rt *rt)
{
	cl_uchar	r;
	int			temp;
	cl_uchar4	*buffer;

	buffer = rt->ocl->dto.buffer;
	temp = matrix[0] * buffer[i - COLS - 1].x +
		matrix[1] * buffer[i - COLS].x +
		matrix[2] * buffer[i - COLS + 1].x +
		matrix[3] * buffer[i - 1].x +
		matrix[4] * buffer[i].x +
		matrix[5] * buffer[i + 1].x +
		matrix[6] * buffer[i + COLS - 1].x +
		matrix[7] * buffer[i + COLS].x +
		matrix[8] * buffer[i + COLS + 1].x;
	if (temp > 0)
		r = (cl_uchar)(temp > 255 ? 255 : temp);
	else
		r = 0;
	return (r);
}

static cl_uchar	calc_g(const int matrix[9], int i, t_rt *rt)
{
	cl_uchar	g;
	int			temp;
	cl_uchar4	*buffer;

	buffer = rt->ocl->dto.buffer;
	temp = matrix[0] * buffer[i - COLS - 1].y +
		matrix[1] * buffer[i - COLS].y +
		matrix[2] * buffer[i - COLS + 1].y +
		matrix[3] * buffer[i - 1].y +
		matrix[4] * buffer[i].y +
		matrix[5] * buffer[i + 1].y +
		matrix[6] * buffer[i + COLS - 1].y +
		matrix[7] * buffer[i + COLS].y +
		matrix[8] * buffer[i + COLS + 1].y;
	if (temp > 0)
		g = (cl_uchar)(temp > 255 ? 255 : temp);
	else
		g = 0;
	return (g);
}

static cl_uchar	calc_b(const int matrix[9], int i, t_rt *rt)
{
	cl_uchar	b;
	int			temp;
	cl_uchar4	*buffer;

	buffer = rt->ocl->dto.buffer;
	temp = matrix[0] * buffer[i - COLS - 1].z +
		matrix[1] * buffer[i - COLS].z +
		matrix[2] * buffer[i - COLS + 1].z +
		matrix[3] * buffer[i - 1].z +
		matrix[4] * buffer[i].z +
		matrix[5] * buffer[i + 1].z +
		matrix[6] * buffer[i + COLS - 1].z +
		matrix[7] * buffer[i + COLS].z +
		matrix[8] * buffer[i + COLS + 1].z;
	if (temp > 0)
		b = (cl_uchar)(temp > 255 ? 255 : temp);
	else
		b = 0;
	return (b);
}

cl_uchar4		calc_matrix_values(const int matrix[9], int i, t_rt *rt)
{
	cl_uchar4	res;

	res = rt->ocl->dto.buffer[i];
	res.x = calc_r(matrix, i, rt);
	res.y = calc_g(matrix, i, rt);
	res.z = calc_b(matrix, i, rt);
	return (res);
}
