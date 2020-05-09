/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

# define MOVE 0.02
# define ANGLE 2

static void		move_cam(t_rt *rt, guint key)
{
	FLT3		step;
	cl_float	move;
	DTO_CAM		*cam;

	cam = &rt->ocl->dto.cam;
	move = (key == 'w' || key == 'd' || key == 'e') ? MOVE : -MOVE;
	step = v3_sub(cam->target, cam->origin);
	if (key == 'a' || key == 'd')
		step = v3_cross(step, cam->up);
	else if (key == 'q' || key == 'e')
		step = v3_cross(step, cam->right);
	step = v3_scale(step, move);
	rt->scene->cam.transform.position = v3_add(cam->origin, step);
	rt->scene->cam.transform.direction = v3_add(cam->target, step);
	update_cam(rt);
}

static void		rotate_cam(t_rt *rt, guint key)
{
	FLT3		step;
	cl_float	angle;
	DTO_CAM		*cam;

	cam = &rt->ocl->dto.cam;
	angle = (key == GDK_KEY_KP_8 || key == GDK_KEY_KP_6) ? -ANGLE : ANGLE;
	step = v3_sub(cam->target, cam->origin);
	if (key == GDK_KEY_KP_6 || key == GDK_KEY_KP_4)
		step = v3_rot_y(step, angle);
	else if (key == GDK_KEY_KP_2 || key == GDK_KEY_KP_8)
		step = v3_rot_x(step, angle);
	rt->scene->cam.transform.direction = v3_add(cam->origin, step);
	update_cam(rt);
}

static gboolean	signal_on_window(GtkWidget *button, GdkEventKey *event,
									gpointer data)
{
	t_rt	*rt;

	if (event->keyval == GDK_KEY_Escape)
	{
		gtk_main_quit();
		return (TRUE);
	}
	rt = (t_rt*)data;
	if (event->keyval == 'w' || event->keyval == 's' ||
			event->keyval == 'a' || event->keyval == 'd' ||
			event->keyval == 'q' || event->keyval == 'e')
		move_cam(rt, event->keyval);
	else if (event->keyval == GDK_KEY_KP_2 || event->keyval == GDK_KEY_KP_4 ||
			event->keyval == GDK_KEY_KP_6 || event->keyval == GDK_KEY_KP_8)
		rotate_cam(rt, event->keyval);
	else
		return (TRUE);
	draw_image(rt);
	return (FALSE);
}

static gboolean	wrapper(GtkWidget *button, GdkEventKey *event, gpointer data)
{
	return (FALSE);
}


void	gtk_set_signals(t_rt *rt)
{
	g_signal_connect(G_OBJECT(rt->gtk->window), "key-press_event",
					G_CALLBACK(signal_on_window), rt);
	g_signal_connect(G_OBJECT(rt->gtk->button), "pressed",
		G_CALLBACK(signal_on_window), rt);
	g_signal_connect(G_OBJECT(rt->gtk->button), "key-press-event",
		G_CALLBACK(signal_on_window), rt);
}
