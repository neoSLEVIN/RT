/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 17:30:21 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/12 00:23:36 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	test_ocl(t_ocl *ocl)
{
	for (int i = 0; i < GLOBAL_WORK_SIZE; ++i)
		ft_printf("%{}d\t", (i % 2 ? FT_BLUE : FT_PURPLE), (int)ocl->mem[0][i]);
	ft_putendl("\n");
}

int	main(int argc, char **argv)
{
	GtkApplication	*app;
	int				status;
	t_ocl			ocl;

	(argc != 1) ? usage(argv[0]) : 0;

//	init_ocl(&ocl);
//	create_cl(&ocl);
//	compile_cl(&ocl);
//
//	set_params_cl(&ocl);
//
//	run_cl(&ocl);
//	test_ocl(&ocl);
//
//	run_cl(&ocl);
//	test_ocl(&ocl);

	app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(run_app), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return (status);
}
