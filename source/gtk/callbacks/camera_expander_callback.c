/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_expander_callback.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:25:06 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:25:06 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	camera_expander_callback(GObject *object, GParamSpec *param_spec,
								gpointer data)
{
	t_rt			*rt;

	(void)param_spec;
	(void)object;
	rt = (t_rt*)data;
	g_idle_add(update_camera_widget, rt);
}
