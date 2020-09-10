/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_camera_widget.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:22:37 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:22:37 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

gboolean	update_camera_widget(gpointer data)
{
	t_rt			*rt;
	t_gtk_camera	*cam;
	FLT3			pos;

	rt = (t_rt*)data;
	cam = &rt->gtk->ui.camera;
	pos = rt->scene->cam.dto->origin;
	if (gtk_expander_get_expanded(GTK_EXPANDER(cam->expander)) &&
		gtk_expander_get_expanded(GTK_EXPANDER(cam->pos_expander)))
	{
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(cam->pos[0].spin), pos.x);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(cam->pos[1].spin), pos.y);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(cam->pos[2].spin), pos.z);
	}
	return (FALSE);
}
