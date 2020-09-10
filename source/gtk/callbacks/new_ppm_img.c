/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_ppm_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:25:51 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:25:51 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	new_texture(GtkButton *button, gpointer data)
{
	t_rt	*rt;
	PPM_IMG	*texture;
	char	*filename;

	(void)button;
	rt = (t_rt*)data;
	if (rt->scene->t_cnt >= MAX_PPM_IMG_COUNT)
		return ;
	if ((filename = get_ppm_filename(PROJ_DIR"extras/textures")) != NULL)
	{
		texture = new_ppm_img_init(rt, filename, &rt->scene->textures, FALSE);
		if (!texture)
			return (ft_strdel(&filename));
		new_ppm_img_update_everything(rt, &rt->gtk->ui.texture, texture, FALSE);
	}
}

void	new_normal_map(GtkButton *button, gpointer data)
{
	t_rt	*rt;
	PPM_IMG	*normal_map;
	char	*filename;

	(void)button;
	rt = (t_rt*)data;
	if (rt->scene->n_cnt >= MAX_PPM_IMG_COUNT)
		return ;
	if ((filename = get_ppm_filename(PROJ_DIR"extras/normalmaps")) != NULL)
	{
		normal_map =
			new_ppm_img_init(rt, filename, &rt->scene->normal_maps, TRUE);
		if (!normal_map)
			return (ft_strdel(&filename));
		new_ppm_img_update_everything(rt, &rt->gtk->ui.normals, normal_map,
			TRUE);
	}
}
