/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_app.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 23:07:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/02 11:59:51 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	print_hello(GtkWidget *widget, gpointer data)
{
	g_print("Hello World\n");
}

gchar	*get_file_name_of_scene()
{
	GtkWidget	*window;
	GtkWidget	*dialog;
	gchar		*filename;

	filename = NULL;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	dialog = gtk_file_chooser_dialog_new("Open File", (GtkWindow*)window,
		GTK_FILE_CHOOSER_ACTION_OPEN,
		GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
		GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);
	if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
		filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (dialog));
	else
		ft_error("Failed to run \"Open file\" window");
	gtk_widget_destroy(dialog);
	gtk_widget_destroy(window);
	return (filename);
}

void	rt_open_warning(GtkApplication *app, gpointer user_data, char *err_msg)
{
	GtkWidget	*window;
	GtkWidget	*button;
	GtkWidget	*button_box;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW (window), "Window");
	gtk_window_set_default_size(GTK_WINDOW (window), 300, 300);

	button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_container_add(GTK_CONTAINER (window), button_box);

	button = gtk_button_new_with_label(err_msg);
	g_signal_connect(button, "clicked", G_CALLBACK (print_hello), NULL);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
	gtk_container_add(GTK_CONTAINER (button_box), button);
	gtk_widget_show_all(window);
}

void	rt_open_window(GtkApplication *app, gpointer user_data)
{
	GtkWidget	*window;
	GtkWidget	*button;
	GtkWidget	*button_box;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW (window), "Window");
	gtk_window_set_default_size(GTK_WINDOW (window), 800, 800);

	button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_container_add(GTK_CONTAINER (window), button_box);

	button = gtk_button_new_with_label("Hello World");
	g_signal_connect(button, "clicked", G_CALLBACK (print_hello), NULL);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
	gtk_container_add(GTK_CONTAINER (button_box), button);
	gtk_widget_show_all(window);
}

void	rt_lights_del(t_list_light **list_light)
{
	if (!list_light || !*list_light)
		return ;
	rt_lights_del(&(*list_light)->next);
	ft_memdel((void**)&(*list_light)->light);
	ft_memdel((void**)list_light);
}

void	rt_shapes_del(t_list_shape **list_shape)
{
	if (!list_shape || !*list_shape)
		return ;
	rt_shapes_del(&(*list_shape)->next);
	ft_memdel(&(*list_shape)->shape);
	ft_memdel((void**)list_shape);
}

void	rt_scene_del(t_scene *scene)
{
	if (!scene)
		return ;
	rt_shapes_del(&scene->shapes);
	rt_lights_del(&scene->lights);
}

void	run_app(GtkApplication *app, gpointer user_data)
{
	gchar		*filename;
	t_scene		scene;

	filename = get_file_name_of_scene();
	scene = parse_scene(filename);
	g_free(filename);
	rt_open_window(app, user_data);
}
