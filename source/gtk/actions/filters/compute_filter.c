/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_filter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:20:22 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:20:23 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static int	is_border(int i, DTO_CAM *cam)
{
	if (i / cam->max_screen.x >= cam->screen_h + cam->diff_screen.y - 1 ||
		i / cam->max_screen.x <= cam->diff_screen.y ||
		i % cam->max_screen.x >= cam->screen_w + cam->diff_screen.x - 1 ||
		i % cam->max_screen.x <= cam->diff_screen.x)
		return (1);
	return (0);
}

static void	update_buff(cl_uchar4 *buffer, t_rt *rt)
{
	int	i;

	i = -1;
	while (++i < ROWS * COLS)
		rt->ocl->dto.buffer[i] = buffer[i];
}

static void	compute_emboss(t_rt *rt)
{
	cl_uchar4	*buffer;
	const int	e_matrix[9] = {0, -1, 0, -1, 5, -1, 0, -1, 0};
	int			i;

	buffer = rt->ocl->dto.filter_buff;
	i = -1;
	while (++i < ROWS * COLS)
		buffer[i] = rt->ocl->dto.buffer[i];
	i = -1;
	while (++i < ROWS * COLS)
	{
		if (!is_border(i, rt->scene->cam.dto))
			buffer[i] = calc_matrix_values(e_matrix, i, rt);
	}
	update_buff(buffer, rt);
}

static void	compute_sharpen(t_rt *rt)
{
	cl_uchar4	*buffer;
	const int	sh_matrix[9] = {-2, -1, 0, -1, 1, 1, 0, 1, 2};
	int			i;

	buffer = rt->ocl->dto.filter_buff;
	i = -1;
	while (++i < ROWS * COLS)
		buffer[i] = rt->ocl->dto.buffer[i];
	i = -1;
	while (++i < ROWS * COLS)
	{
		if (!is_border(i, rt->scene->cam.dto))
			buffer[i] = calc_matrix_values(sh_matrix, i, rt);
	}
	update_buff(buffer, rt);
}

void		compute_filter(t_rt *rt)
{
	if (rt->scene->filter == BLUR)
		compute_blur(rt);
	else if (rt->scene->filter == EMBOSS)
		compute_emboss(rt);
	else if (rt->scene->filter == SHARPEN)
		compute_sharpen(rt);
}
