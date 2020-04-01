/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 17:30:21 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/01 03:20:32 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	main(int argc, char **argv)
{
	t_ocl	ocl;
	int		sum = 0;

	init_ocl(&ocl);
	create_cl(&ocl);
	compile_cl(&ocl);
	setting_cl(&ocl);
	run_cl(&ocl);

	gtk_init(&argc, &argv);

	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	gtk_widget_show(window);

	gtk_main();

	return (0);
}
