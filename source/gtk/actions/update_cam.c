/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:55 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

# define MOVE 0.02
# define ANGLE 2

void	update_cam(t_rt *rt)
{
	int	err;

	translate_cam(&rt->ocl->dto.cam, &rt->scene->cam);
	err = clSetKernelArg(rt->ocl->kernel, 4, sizeof(DTO_CAM),
						&(rt->ocl->dto.cam));
	check_error_cl(err,"clSetKernelArg", "cam");
}

void	move_cam(t_rt *rt, guint key)
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

void	rotate_cam(t_rt *rt, guint key)
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
