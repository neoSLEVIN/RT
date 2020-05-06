/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 17:30:21 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/05 07:13:49 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	usage(char *app_name)
{
	ft_printf("Usage:\t%s\n", app_name);
	exit(1);
}

int			main(int argc, char **argv)
{
	GTK_DATA	*gtk;

	(argc != 1) ? usage(argv[0]) : 0;
	gtk_init(&argc, &argv);
	gtk = new_gtk(new_scene(), new_ocl());
	draw_image(NULL, &gtk->rt);
	gtk_widget_show_all(gtk->window);
	gtk_main();
	gtk_clear(&gtk);
	return (0);
}
