/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_ppm_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:21:52 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:21:53 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static int	get_index_by_iter(t_gtk_textures *gtk_ppm, GtkTreeIter *iter)
{
	char	*str;
	int		num;

	str = gtk_tree_model_get_string_from_iter(gtk_ppm->model, iter);
	if (!str)
		ft_error("Bad iter (get_index_by_iter)");
	num = ft_atoi(str);
	g_free(str);
	return (num);
}

static void	decrease_ppm_img_indexes(SHAPE *shape, int index,
									_Bool is_normal_map)
{
	if (is_normal_map)
	{
		while (shape)
		{
			if (shape->dto && shape->dto->normal_map.id >= index)
				--shape->dto->normal_map.id;
			shape = shape->next;
		}
	}
	else
	{
		while (shape)
		{
			if (shape->dto && shape->dto->texture.id >= index)
				--shape->dto->texture.id;
			shape = shape->next;
		}
	}
}

static void	free_ppm_img_data(PPM_IMG **ppm_del, PPM_IMG **ppm_lst)
{
	if (*ppm_lst == *ppm_del)
		*ppm_lst = (*ppm_del)->next;
	((*ppm_del)->prev) ? ((*ppm_del)->prev->next = (*ppm_del)->next) : 0;
	((*ppm_del)->next) ? ((*ppm_del)->next->prev = (*ppm_del)->prev) : 0;
	((*ppm_del)->name) ? ft_strdel(&(*ppm_del)->name) : 0;
	((*ppm_del)->path) ? ft_strdel(&(*ppm_del)->path) : 0;
	ft_memdel((void**)ppm_del);
}

void		delete_texture(t_rt *rt)
{
	GtkTreeIter	iter;
	PPM_IMG		*ppm;
	int			index;

	if (gtk_tree_model_get_iter(rt->gtk->ui.texture.model, &iter,
								rt->gtk->ui.texture.path))
	{
		index = get_index_by_iter(&rt->gtk->ui.texture, &iter);
		gtk_tree_model_get(rt->gtk->ui.texture.model, &iter,
						PPM_POINTER_COL, &ppm, -1);
		decrease_ppm_img_indexes(rt->scene->shapes, index, FALSE);
		gtk_combo_box_text_remove(GTK_COMBO_BOX_TEXT(
			rt->gtk->ui.shape->texture.texture_combo), index + 5);
		update_flags(&rt->info->update_shapes, &rt->info->update_s_tex);
		update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
						&rt->info->update_shapes);
		free_ppm_img_data(&ppm, &rt->scene->textures);
		gtk_tree_store_remove(rt->gtk->ui.texture.store, &iter);
		realloc_ppm_img_dto(&rt->ocl->dto.textures, rt->scene->textures,
							--rt->scene->t_cnt);
		update_textures_arg(rt->ocl, rt->scene->t_cnt);
		rt->info->update = TRUE;
	}
	gtk_tree_path_free(rt->gtk->ui.texture.path);
}

void		delete_normal_map(t_rt *rt)
{
	GtkTreeIter	iter;
	PPM_IMG		*ppm;
	int			index;

	if (gtk_tree_model_get_iter(rt->gtk->ui.normals.model, &iter,
								rt->gtk->ui.normals.path))
	{
		index = get_index_by_iter(&rt->gtk->ui.normals, &iter);
		gtk_tree_model_get(rt->gtk->ui.normals.model, &iter,
						PPM_POINTER_COL, &ppm, -1);
		decrease_ppm_img_indexes(rt->scene->shapes, index, TRUE);
		gtk_combo_box_text_remove(GTK_COMBO_BOX_TEXT(
			rt->gtk->ui.shape->texture.normals_combo), index + 1);
		update_flags(&rt->info->update_shapes, &rt->info->update_s_tex);
		update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
						&rt->info->update_shapes);
		free_ppm_img_data(&ppm, &rt->scene->normal_maps);
		gtk_tree_store_remove(rt->gtk->ui.normals.store, &iter);
		realloc_ppm_img_dto(&rt->ocl->dto.normal_maps, rt->scene->normal_maps,
							--rt->scene->n_cnt);
		update_normal_maps_arg(rt->ocl, rt->scene->n_cnt);
		rt->info->update = TRUE;
	}
	gtk_tree_path_free(rt->gtk->ui.normals.path);
}
