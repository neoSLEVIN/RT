/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_gtk.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/10 05:54:45 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	new_gtk(t_rt *rt, const char *filename, GtkWidget **win)
{
	if (!(rt->gtk = (t_gtk*)malloc(sizeof(t_gtk))))
		ft_error("Can't allocate memory");
	rt->gtk->window = *win;
	gtk_set_main_window(rt->gtk, filename);
	gtk_set_widgets(rt->gtk, rt);
	gtk_set_signals(rt);
	gtk_set_positions(rt->gtk);
}
