/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_main_window.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/10 07:04:24 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_main_window(t_gtk *gtk, const char *filename)
{
	if (!(gtk->titles[0] = ft_strjoin("RT | ", filename)))
		ft_error("Can't allocate memory");
	if (!(gtk->titles[1] = ft_strjoin(gtk->titles[0], " | Loading...")))
		ft_error("Can't allocate memory");
	gtk_window_set_title(GTK_WINDOW(gtk->window), gtk->titles[0]);
	gtk_window_set_default_size(GTK_WINDOW(gtk->window),
		COLS + UI_WIDTH, ROWS);
	gtk_window_set_position(GTK_WINDOW(gtk->window), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(gtk->window), FALSE);
	g_signal_connect(G_OBJECT(gtk->window), "destroy",
		G_CALLBACK(gtk_main_quit), NULL);
}
