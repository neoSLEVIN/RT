/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:25:46 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:25:47 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static LIGHT	*get_default_light(LIGHT *light, DTO_LIGHT *dto)
{
	light->tree_iter = NULL;
	light->name = NULL;
	light->next = NULL;
	light->prev = NULL;
	light->dto = dto;
	return (light);
}

static void		init_default_light_dto(DTO_CAM *cam, DTO_LIGHT *dto)
{
	dto->type = POINT;
	dto->intensity = 0.3f;
	dto->position = v3_add(v3_add(cam->origin,
							v3_scale(cam->forward, 10)),
							v3_scale(cam->upguide, 5));
	dto->direction = v3_scale(cam->upguide, -1.0f);
}

static LIGHT	*new_light_init(t_rt *rt)
{
	LIGHT	*light;
	LIGHT	*temp;

	if (!(light = (LIGHT*)malloc(sizeof(LIGHT))))
		ft_error("Can't allocate memory");
	get_default_light(light, &rt->info->default_light_dto);
	init_default_light_dto(&rt->ocl->dto.cam, light->dto);
	light->name = unnamed_obj(rt->scene->l_cnt + 1, "Light");
	if (rt->scene->lights == NULL)
	{
		rt->scene->lights = light;
		return (light);
	}
	temp = rt->scene->lights;
	while (temp->next)
		temp = temp->next;
	temp->next = light;
	light->prev = temp;
	return (light);
}

static void		new_light_update_everything(t_rt *rt, t_gtk_lights *gtk_lights,
											LIGHT *light)
{
	GtkTreePath	*path;
	char		*type;

	gtk_tree_store_append(gtk_lights->store, &gtk_lights->iter, NULL);
	if (!(light->tree_iter = (void*)gtk_tree_iter_copy(&gtk_lights->iter)))
		ft_error("Can't allocate memory");
	type = get_light_type_name(light->dto->type);
	gtk_tree_store_set(gtk_lights->store, &gtk_lights->iter, LIGHT_NAME_COL,
		light->name, LIGHT_TYPE_COL, type, LIGHT_POINTER_COL, light, -1);
	ft_strdel(&type);
	if (!(path = gtk_tree_model_get_path(gtk_lights->model, light->tree_iter)))
		ft_error("Can't allocate memory");
	gtk_tree_selection_select_path(gtk_lights->select, path);
	gtk_tree_view_scroll_to_cell(GTK_TREE_VIEW(gtk_lights->tree),
		path, NULL, FALSE, 0, 0);
	gtk_tree_path_free(path);
	realloc_lights_dto(&rt->ocl->dto.lights, rt->scene->lights,
					++rt->scene->l_cnt);
	update_flags(&rt->info->update_lights, &rt->info->update_l_cnt);
	update_lights_arg(rt->ocl, &rt->info->update_l_cnt,
					&rt->info->update_lights);
	rt->info->update = TRUE;
	rt->gtk->ui.light->light = light;
	update_flags(&rt->info->update_l_name, &rt->info->update_l_params);
	g_idle_add(update_light_widget, rt);
}

void			new_light(GtkButton *button, gpointer data)
{
	t_rt	*rt;
	LIGHT	*light;

	(void)button;
	rt = (t_rt*)data;
	if (rt->scene->l_cnt < MAX_LIGHTS_COUNT)
	{
		light = new_light_init(rt);
		new_light_update_everything(rt, &rt->gtk->ui.lights, light);
	}
}
