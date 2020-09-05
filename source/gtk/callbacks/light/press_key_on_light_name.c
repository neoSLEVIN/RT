/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key_on_light_name.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:23:05 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:23:06 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

gboolean	press_key_on_light_name(GtkWidget *entry_name, GdkEventKey *event,
									gpointer data)
{
	t_rt		*rt;
	const gchar	*text;

	rt = (t_rt*)data;
	ASSERT_LIGHT(rt->gtk->ui.light->light);
	if (event->keyval == GDK_KEY_Return)
	{
		gtk_widget_set_visible(entry_name, FALSE);
		gtk_widget_set_visible(entry_name, TRUE);
		text = gtk_entry_get_text(GTK_ENTRY(entry_name));
		ft_strdel(&rt->gtk->ui.light->light->name);
		if (!(rt->gtk->ui.light->light->name = ft_strdup(text)))
			ft_error("Can't allocate memory");
		gtk_tree_store_set(rt->gtk->ui.lights.store,
						(GtkTreeIter*)rt->gtk->ui.light->light->tree_iter,
						LIGHT_NAME_COL, text,
						-1);
		gtk_frame_set_label(GTK_FRAME(rt->gtk->ui.light->frame),
						rt->gtk->ui.light->light->name);
	}
	return (FALSE);
}
