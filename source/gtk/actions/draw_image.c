/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/29 02:03:00 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

/*
**
** Эффект cartoon
** |	|	|
** V	V	V
*/

typedef struct	s_cartoon
{
	cl_uint3	average;
	cl_uint		segment_size;
	cl_int2		count_of_segments;
	cl_int2		segment;
	cl_int2		pix_of_segment;
	cl_int		pix;
}				t_cartoon;

void	init_cartoon(t_cartoon *cartoon)
{
	cartoon->average = (cl_uint3){0, 0, 0};
	cartoon->segment_size = 5;
	cartoon->count_of_segments.x = (COLS % cartoon->segment_size == 0) ?
				(COLS / cartoon->segment_size) : (COLS / cartoon->segment_size + 1);
	cartoon->count_of_segments.y = (ROWS % cartoon->segment_size == 0) ?
				(ROWS / cartoon->segment_size) : (ROWS / cartoon->segment_size + 1);
	cartoon->segment = (cl_int2){-1, -1};
	cartoon->pix_of_segment = (cl_int2){-1, -1};
	cartoon->pix = -1;
}

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

void	put_pixel_to_average_sum(cl_uchar4 *pixel, cl_uint3 *average)
{
	average->x += (cl_uint)pixel->x;
	average->y += (cl_uint)pixel->y;
	average->z += (cl_uint)pixel->z;
}

void	put_average_to_pixel(cl_uchar4 *pixel, cl_uint3 *average)
{
	pixel->x = (cl_uchar)average->x;
	pixel->y = (cl_uchar)average->y;
	pixel->z = (cl_uchar)average->z;
}

void	segment_loop(void (*action_for_pixel)(cl_uchar4 *, cl_uint3 *),
					cl_uchar4 *buffer, t_cartoon *cartoon)
{
	cl_int2	segment_start;

	segment_start.y = cartoon->segment.y * cartoon->segment_size;
	segment_start.x = cartoon->segment.x * cartoon->segment_size;
	cartoon->pix_of_segment.y = -1;
	while (++cartoon->pix_of_segment.y < cartoon->segment_size &&
		(segment_start.y + cartoon->pix_of_segment.y) < ROWS)
	{
		cartoon->pix_of_segment.x = 0;
		cartoon->pix =
			(segment_start.y + cartoon->pix_of_segment.y) * COLS + segment_start.x;
		while (cartoon->pix_of_segment.x < cartoon->segment_size &&
			(segment_start.x + cartoon->pix_of_segment.x) < COLS)
		{
			action_for_pixel(&buffer[cartoon->pix], &cartoon->average);
			++cartoon->pix_of_segment.x;
			++cartoon->pix;
		}
	}
}

void	compute_cartoon(t_rt *rt)
{
	cl_uchar4	*buffer;
	t_cartoon	cartoon;

	buffer = rt->ocl->dto.buffer;
	init_cartoon(&cartoon);
	while (++cartoon.segment.y < cartoon.count_of_segments.y)
	{
		cartoon.segment.x = -1;
		while (++cartoon.segment.x < cartoon.count_of_segments.x)
		{
			cartoon.average = (cl_uint3){0, 0, 0};
			segment_loop(put_pixel_to_average_sum, buffer, &cartoon);
			cartoon.average =
				get_average_from_sum(&cartoon.average,
					cartoon.pix_of_segment.y * cartoon.pix_of_segment.x);
			segment_loop(put_average_to_pixel, buffer, &cartoon);
		}
	}
}

/*
**
** ^	^	^
** |	|	|
** Эффект cartoon
*/


/*
**
** Фильтры blur, emboss, sharpen
**
*/

int		is_border(int i)
{
	if (i / COLS == 0)
		return (1);
	if (i % ROWS == 0)
		return (1);
	if (i % COLS == COLS - 1)
		return (1);
	if (i / COLS == ROWS - 1)
		return (1);
	return (0);
}

cl_uchar		calc_r(int matrix[9], int i, t_rt *rt, int div)
{
	cl_uchar 	r;
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
	temp = temp / div;
	if (temp > 0)
		r = (cl_uchar)(temp > 255 ? 255 : temp);
	else
		r = 0;
	return (r);
}

cl_uchar		calc_g(int matrix[9], int i, t_rt *rt, int div)
{
	cl_uchar 	g;
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
	temp = temp / div;
	if (temp > 0)
		g = (cl_uchar)(temp > 255 ? 255 : temp);
	else
		g = 0;
	return (g);
}

cl_uchar		calc_b(int matrix[9], int i, t_rt *rt, int div)
{
	cl_uchar 	b;
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
	temp = temp / div;
	if (temp > 0)
		b = (cl_uchar)(temp > 255 ? 255 : temp);
	else
		b = 0;
	return (b);
}


cl_uchar4	calc_matrix_values(int matrix[9], int i, t_rt *rt, int div)
{
	cl_uchar4	res;

	res = rt->ocl->dto.buffer[i];
	res.x = calc_r(matrix, i, rt, div);
	res.y = calc_g(matrix, i, rt, div);
	res.z = calc_b(matrix, i, rt, div);
	return (res);
}

void	update_buff(cl_uchar4 *buffer, t_rt *rt)
{
	int	i;
	
	/*
	** Вносим новые значения в старый буфер,
	*/
	i = -1;
	while (++i < ROWS * COLS)
		rt->ocl->dto.buffer[i] = buffer[i];
}

void	compute_blur(t_rt *rt)
{
	cl_uchar4	*buffer;
	int			b_matrix[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
	int			i;
	
	/*
	** Дублируем массив пиксилей в новый массив,
	** где будут происходить изменения
	*/
	buffer = (cl_uchar4*)malloc(sizeof(cl_uchar4) * rt->ocl->work_size);
	i = -1;
	while (++i < ROWS * COLS)
		buffer[i] = rt->ocl->dto.buffer[i];
	i = -1;
	/*Накладываем матрицу размытия*/
	while (++i < ROWS * COLS)
	{
		if (!is_border(i))
			buffer[i] = calc_matrix_values(b_matrix, i, rt, 9);
	}
	update_buff(buffer, rt);
	free(buffer);
}

void	compute_emboss(t_rt *rt)
{
	cl_uchar4	*buffer;
	int			e_matrix[9] = {-2, -1, 0, -1, 1, 1, 0, 1, 2};
	int			i;
	
	/*
	** Дублируем массив пиксилей в новый массив,
	** где будут происходить изменения
	*/
	buffer = (cl_uchar4*)malloc(sizeof(cl_uchar4) * rt->ocl->work_size);
	i = -1;
	while (++i < ROWS * COLS)
		buffer[i] = rt->ocl->dto.buffer[i];
	i = -1;
	/*Накладываем матрицу вдавливания*/
	while (++i < ROWS * COLS)
	{
		if (!is_border(i))
			buffer[i] = calc_matrix_values(e_matrix, i, rt, 1);
	}
	update_buff(buffer, rt);
	free(buffer);
}

void	compute_sharpen(t_rt *rt)
{
	cl_uchar4	*buffer;
	int			sh_matrix[9] = {-2, -1, 0, -1, 1, 1, 0, 1, 2};
	int			i;
	
	/*
	** Дублируем массив пиксилей в новый массив,
	** где будут происходить изменения
	*/
	buffer = (cl_uchar4*)malloc(sizeof(cl_uchar4) * rt->ocl->work_size);
	i = -1;
	while (++i < ROWS * COLS)
		buffer[i] = rt->ocl->dto.buffer[i];
	i = -1;
	/*Накладываем матрицу четкости*/
	while (++i < ROWS * COLS)
	{
		if (!is_border(i))
			buffer[i] = calc_matrix_values(sh_matrix, i, rt, 1);
	}
	update_buff(buffer, rt);
	free(buffer);
}

static gboolean	compute_draw(gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	run_cl(rt->ocl);
	//compute_cartoon(rt);
	compute_blur(rt);
	//compute_emboss(rt);
	//compute_sharpen(rt);
	
	gtk_image_set_from_pixbuf(GTK_IMAGE(rt->gtk->img.image),
										rt->gtk->img.pixbuf);
	return (FALSE);
}

void			draw_image(t_rt *rt)
{
	g_idle_add(compute_draw, rt);
}
