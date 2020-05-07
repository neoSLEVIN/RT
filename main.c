/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 17:30:21 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/07 04:53:54 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

// TODO delete it before defending
void	test_ocl(t_ocl *ocl)
{
	for (int i = 0; i < ocl->work_size; ++i)
		if (ocl->dto.buffer[i].x != 0 || ocl->dto.buffer[i].y != 0 || ocl->dto.buffer[i].z != 0)
			ft_printf("%{}.f %{}.f %{}.f\t",
					  FT_BLUE, ocl->dto.buffer[i].x,
					  FT_PURPLE, ocl->dto.buffer[i].y,
					  FT_YELLOW, ocl->dto.buffer[i].z);
	ft_putendl("\n");
}

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
	rt.ocl = new_ocl();
	rt.scene = new_scene();
	new_gtk(&rt);
	init_info(&rt.info);
	setting_cl(rt.ocl, rt.scene);
	draw_image(&rt);
	gtk_widget_show_all(rt.gtk->window);
	gtk_main();
	clear_rt(&rt);
	return (0);
}
