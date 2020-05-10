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

void	new_gtk(t_rt *rt)
{
	if ((rt->gtk = g_slice_new(t_gtk)) == NULL)
		ft_error("Can't allocate memory");
	gtk_set_main_window(rt->gtk);
	gtk_set_objects(rt->gtk, rt);
	gtk_set_signals(rt);
	gtk_set_positions(rt->gtk);
}
