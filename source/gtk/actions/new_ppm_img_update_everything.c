/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_ppm_img_update_everything.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:22:19 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:22:20 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void		new_ppm_img_update_everything(t_rt *rt, t_gtk_textures *gtk_ppm,
										PPM_IMG *new_texture,
										_Bool is_normal_map)
{
	DTO_PPM_IMG	*dto;

	dto = new_texture->dto;
	gtk_tree_store_append(gtk_ppm->store, &gtk_ppm->iter, NULL);
	gtk_tree_store_set(gtk_ppm->store, &gtk_ppm->iter,
		PPM_NAME_COL, new_texture->name, PPM_PATH_COL, new_texture->path,
		PPM_POINTER_COL, new_texture, -1);
	if (is_normal_map)
	{
		realloc_ppm_img_dto(&rt->ocl->dto.normal_maps, rt->scene->normal_maps,
							++rt->scene->n_cnt);
		update_normal_maps_arg(rt->ocl, rt->scene->n_cnt);
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(
			rt->gtk->ui.shape->texture.normals_combo), new_texture->name);
	}
	else
	{
		realloc_ppm_img_dto(&rt->ocl->dto.textures, rt->scene->textures,
							++rt->scene->t_cnt);
		update_textures_arg(rt->ocl, rt->scene->t_cnt);
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(
			rt->gtk->ui.shape->texture.texture_combo), new_texture->name);
	}
	ft_memdel((void**)&dto);
}
