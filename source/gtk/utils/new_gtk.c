/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_gtk.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 21:06:05 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/07 05:09:22 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	new_gtk(t_rt *rt)
{
	if ((rt->gtk = g_slice_new(t_gtk)) == NULL)
		ft_error("Can't allocate memory");
	gtk_set_default_params(rt->gtk);
	gtk_set_main_window(rt->gtk);
	gtk_set_objects(rt->gtk, rt->ocl->dto.buffer);
	gtk_set_signals(rt);
	gtk_set_positions(rt->gtk);
}
