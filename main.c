/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/06/01 01:35:40 by cschoen          ###   ########.fr       */
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
	t_rt	rt;

	(argc != 1) ? usage(argv[0]) : 0;
	gtk_init(&argc, &argv);
	init_info(&rt.info);
	new_ocl(&rt.ocl);
	new_scene(&rt.scene);
	setting_cl(rt.ocl, rt.scene, rt.info);
	new_gtk(&rt);
	draw_image(&rt);
	gtk_widget_show_all(rt.gtk->window);
	gtk_main();
//	clear_rt(&rt);
	return (0);
}
