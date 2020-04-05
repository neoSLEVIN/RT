/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 17:30:21 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/05 00:06:39 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

//int	main(int argc, char **argv)
//{
//
//	gtk_init(&argc, &argv);
//
//	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//
//	gtk_widget_show(window);
//
//	gtk_main();
//
//	return (0);
//}

static void	print_hello(GtkWidget *widget, gpointer data)
{
	g_print("Hello World\n");
}

static void	activate(GtkApplication *app, gpointer user_data)
{
	GtkWidget	*window;
	GtkWidget	*button;
	GtkWidget	*button_box;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW (window), "Window");
	gtk_window_set_default_size(GTK_WINDOW (window), 200, 200);

	button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_container_add(GTK_CONTAINER (window), button_box);

	button = gtk_button_new_with_label("Hello World");
	g_signal_connect(button, "clicked", G_CALLBACK (print_hello), NULL);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
	gtk_container_add(GTK_CONTAINER (button_box), button);

	gtk_widget_show_all(window);
}

void	test_ocl(t_ocl *ocl)
{
	for (int i = 0; i < GLOBAL_WORK_SIZE; ++i)
		ft_printf("%d\t", (int)ocl->mem[0][i]);
	ft_putendl("\n");
}

int	main(int argc, char **argv)
{
	GtkApplication	*app;
	int				status;
	t_ocl			ocl;

	(argc != 1) ? usage(argv[0]) : 0;
	init_ocl(&ocl);
	create_cl(&ocl);
	compile_cl(&ocl);
	set_params_cl(&ocl);
	run_cl(&ocl);

	test_ocl(&ocl);

 	app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	run_cl(&ocl);

	test_ocl(&ocl);
	parse(TEMP_SRC_JSON);

	return (status);
}
