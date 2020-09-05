/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_blur.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:20:09 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:20:11 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	init_blur(t_blur *blur, unsigned segment_size, INT2 screen)
{
	blur->average = (cl_uint3){0, 0, 0};
	blur->segment_size = segment_size;
	blur->count_of_segments.x = (screen.x % blur->segment_size == 0) ?
		(screen.x / blur->segment_size) : (screen.x / blur->segment_size + 1);
	blur->count_of_segments.y = (screen.y % blur->segment_size == 0) ?
		(screen.y / blur->segment_size) : (screen.y / blur->segment_size + 1);
	blur->segment = (cl_int2){-1, -1};
	blur->pix_of_segment = (cl_int2){-1, -1};
	blur->pix = -1;
}

static void	segment_loop(void (*action_for_pixel)(cl_uchar4 *, cl_uint3 *),
					cl_uchar4 *buffer, t_blur *blur, DTO_CAM *cam)
{
	cl_int2	segment_start;

	segment_start.y = blur->segment.y * blur->segment_size;
	segment_start.x = blur->segment.x * blur->segment_size;
	blur->pix_of_segment.y = -1;
	while (++blur->pix_of_segment.y < blur->segment_size &&
			(segment_start.y + blur->pix_of_segment.y) < cam->screen_h)
	{
		blur->pix_of_segment.x = 0;
		blur->pix =
			(segment_start.y + blur->pix_of_segment.y + cam->diff_screen.y) *
			COLS + (segment_start.x + cam->diff_screen.x);
		while (blur->pix_of_segment.x < blur->segment_size &&
				(segment_start.x + blur->pix_of_segment.x) < cam->screen_w)
		{
			action_for_pixel(&buffer[blur->pix], &blur->average);
			++blur->pix_of_segment.x;
			++blur->pix;
		}
	}
}

void		compute_blur(t_rt *rt)
{
	cl_uchar4	*buffer;
	t_blur		blur;

	buffer = rt->ocl->dto.buffer;
	init_blur(&blur, (unsigned)rt->scene->filter_params.x,
		(INT2){rt->scene->cam.dto->screen_w, rt->scene->cam.dto->screen_h});
	while (++blur.segment.y < blur.count_of_segments.y)
	{
		blur.segment.x = -1;
		while (++blur.segment.x < blur.count_of_segments.x)
		{
			blur.average = (cl_uint3){0, 0, 0};
			segment_loop(put_pixel_to_average_sum, buffer, &blur,
						rt->scene->cam.dto);
			blur.average =
				get_average_from_sum(&blur.average,
					blur.pix_of_segment.y * blur.pix_of_segment.x);
			segment_loop(put_average_to_pixel, buffer, &blur,
						rt->scene->cam.dto);
		}
	}
}
