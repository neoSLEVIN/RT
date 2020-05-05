/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 17:30:21 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/04 21:51:44 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	usage(char *app_name)
{
	ft_printf("Usage:\t%s\n", app_name);
	exit(1);
}

int			main(int argc, char **argv)
{
	t_rt	rt;

	(argc != 1) ? usage(argv[0]) : 0;
	gtk_init(&argc, &argv);
	rt_init(&rt);
	draw_image(NULL, &rt.gtk->img);
	gtk_widget_show_all(rt.gtk->window);
	gtk_main();
	rt_clear(&rt);
	return (0);
}
