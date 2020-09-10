/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:25:55 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:25:55 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static SHAPE	*new_shape_init(t_rt *rt)
{
	SHAPE	*shape;
	SHAPE	*temp;

	if (!(shape = (SHAPE*)malloc(sizeof(SHAPE))))
		ft_error("Can't allocate memory");
	get_default_shape(shape, &rt->info->default_shape_dto);
	init_default_shape_dto(&rt->ocl->dto.cam, shape->dto);
	shape->name = unnamed_obj(rt->scene->s_cnt + 1, "Shape");
	if (rt->scene->shapes == NULL)
	{
		rt->scene->shapes = shape;
		return (shape);
	}
	temp = rt->scene->shapes;
	while (temp->next)
		temp = temp->next;
	temp->next = shape;
	shape->prev = temp;
	return (shape);
}

static gboolean	new_shape_safe(gpointer data)
{
	t_rt	*rt;
	SHAPE	*shape;

	rt = (t_rt*)data;
	shape = new_shape_init(rt);
	new_shape_update_everything(rt, &rt->gtk->ui.shapes, shape);
	return (FALSE);
}

void			new_shape(GtkButton *button, gpointer data)
{
	(void)button;
	if (((t_rt*)data)->scene->s_cnt < MAX_SHAPES_COUNT)
		g_idle_add(new_shape_safe, data);
}
