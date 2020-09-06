/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key_on_shape_name.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:23:44 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:23:44 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

gboolean	press_key_on_shape_name(GtkWidget *entry_name, GdkEventKey *event,
									gpointer data)
{
	t_rt		*rt;
	const gchar	*text;

	rt = (t_rt*)data;
	ASSERT_SHAPE(rt->gtk->ui.shape->shape);
	if (event->keyval == GDK_KEY_Return)
	{
		gtk_widget_set_visible(entry_name, FALSE);
		gtk_widget_set_visible(entry_name, TRUE);
		text = gtk_entry_get_text(GTK_ENTRY(entry_name));
		ft_strdel(&rt->gtk->ui.shape->shape->name);
		if (!(rt->gtk->ui.shape->shape->name = ft_strdup(text)))
			ft_error("Can't allocate memory");
		gtk_tree_store_set(rt->gtk->ui.shapes.store,
						(GtkTreeIter*)rt->gtk->ui.shape->shape->tree_iter,
						S_NAME_COL, text,
						-1);
		gtk_frame_set_label(GTK_FRAME(rt->gtk->ui.shape->frame),
						rt->gtk->ui.shape->shape->name);
	}
	return (FALSE);
}
