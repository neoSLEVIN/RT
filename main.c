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

int	main(int argc, char **argv)
{
	t_rt	rt;

	(argc != 1) ? usage(argv[0]) : 0;
	gtk_init(&argc, &argv);
	init_info(&rt.info);
	new_ocl(&rt.ocl);
	new_scene(&rt.scene);
	setting_cl(rt.ocl, rt.scene, rt.info);
	new_gtk(&rt, rt.scene->filename);
	draw_image(&rt);
	show_widgets(&rt);
	gtk_main();
	exit(0);
	return (0);
}
