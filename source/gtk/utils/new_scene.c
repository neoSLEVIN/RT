/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 14:45:28 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/04 22:22:05 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static gchar	*get_file_name_of_scene(void)
{
	GtkWidget	*window;
	GtkWidget	*dialog;
	gchar		*filename;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	dialog = gtk_file_chooser_dialog_new("Open File", (GtkWindow*)window,
		GTK_FILE_CHOOSER_ACTION_OPEN,
		"_Cancel", GTK_RESPONSE_CANCEL,
		"_Open", GTK_RESPONSE_ACCEPT, NULL);
	if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
		filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
	else
	{
		ft_printf("Close \"Open File\" tab");
		exit(0);
	}
	gtk_widget_destroy(dialog);
	gtk_widget_destroy(window);
	return (filename);
}

t_scene			*new_scene(void)
{
	gchar	*filename;
	t_scene	*scene;

	filename = get_file_name_of_scene();
	scene = parse_scene(filename);
	g_free(filename);
	return (scene);
}
