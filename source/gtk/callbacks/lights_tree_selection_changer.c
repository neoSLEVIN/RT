/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_tree_selection_changer.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:25:38 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:25:38 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	lights_tree_selection_changer(GtkTreeSelection *selection,
										gpointer data)
{
	t_rt			*rt;
	GtkTreeIter		iter;
	struct s_light	*light;

	rt = (t_rt*)data;
	if (gtk_tree_selection_get_selected(selection, &rt->gtk->ui.lights.model,
										&iter))
	{
		gtk_tree_model_get(rt->gtk->ui.lights.model, &iter,
			LIGHT_POINTER_COL, &light,
			-1);
		rt->gtk->ui.light->light = light;
		update_flags(&rt->info->update_l_name, &rt->info->update_l_params);
		g_idle_add(update_light_widget, rt);
	}
}
