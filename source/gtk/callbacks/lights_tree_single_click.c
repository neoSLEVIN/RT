/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_tree_single_click.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:25:43 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:25:43 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void		free_light_data(LIGHT *light, t_rt *rt)
{
	gtk_tree_iter_free(light->tree_iter);
	if (rt->gtk->ui.light->light == light)
	{
		rt->gtk->ui.light->light = NULL;
		gtk_expander_set_expanded(GTK_EXPANDER(rt->gtk->ui.light->expander),
									FALSE);
	}
	(light->name) ? ft_strdel(&light->name) : 0;
	(rt->scene->lights == light) ? (rt->scene->lights = light->next) : 0;
	(light->prev) ? (light->prev->next = light->next) : 0;
	(light->next) ? (light->next->prev = light->prev) : 0;
}

static gboolean	delete_light(gpointer data)
{
	t_rt		*rt;
	GtkTreeIter	iter;
	LIGHT		*light;

	rt = (t_rt*)data;
	if (gtk_tree_model_get_iter(rt->gtk->ui.lights.model, &iter,
								rt->gtk->ui.lights.path))
	{
		gtk_tree_model_get(rt->gtk->ui.lights.model, &iter,
			LIGHT_POINTER_COL, &light, -1);
		gtk_tree_store_remove(rt->gtk->ui.lights.store, &iter);
		free_light_data(light, rt);
		ft_memdel((void**)&light);
		realloc_lights_dto(&rt->ocl->dto.lights, rt->scene->lights,
							--rt->scene->l_cnt);
		update_flags(&rt->info->update_lights, &rt->info->update_l_cnt);
		update_lights_arg(rt->ocl, &rt->info->update_l_cnt,
							&rt->info->update_lights);
		rt->info->update = TRUE;
	}
	gtk_tree_path_free(rt->gtk->ui.lights.path);
	return (FALSE);
}

gboolean		lights_tree_single_click(GtkTreeView *tree,
										GdkEventButton *event, gpointer data)
{
	t_rt				*rt;
	GtkTreeViewColumn	*column;

	if (event->type == GDK_BUTTON_PRESS && event->button == 1)
	{
		rt = (t_rt*)data;
		if (!gtk_tree_view_get_path_at_pos(tree, event->x, event->y,
				&rt->gtk->ui.lights.path, &column, NULL, NULL))
			return (FALSE);
		if (column == gtk_tree_view_get_column(tree, LIGHT_DELETE_COL))
		{
			delete_light(rt);
			return (TRUE);
		}
		gtk_tree_path_free(rt->gtk->ui.lights.path);
	}
	return (FALSE);
}
