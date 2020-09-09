/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste_shape.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:25:18 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:25:18 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void		copy_shape(t_rt *rt)
{
	if (rt->info->s_copy && rt->info->s_marker)
	{
		ft_memdel((void**)&rt->info->s_copy->dto);
		ft_strdel(&rt->info->s_copy->name);
		ft_memdel((void**)&rt->info->s_copy);
	}
	if (rt->info->s_marker)
	{
		if (!(rt->info->s_copy = (SHAPE*)malloc(sizeof(SHAPE))))
			ft_error("Can't allocate memory");
		get_default_shape(rt->info->s_copy, NULL);
		if (!(rt->info->s_copy->dto = (DTO_SHAPE*)malloc(sizeof(DTO_SHAPE))))
			ft_error("Can't allocate memory");
		*rt->info->s_copy->dto = *rt->info->s_marker->dto;
		if (!(rt->info->s_copy->name = ft_strdup(rt->info->s_marker->name)))
			ft_error("Can't allocate memory");
	}
}

static void	update_positions(DTO_SHAPE *dto, FLT3 new_position)
{
	FLT3	diff;
	int		i;

	i = -1;
	diff = v3_sub(new_position, dto->transform.position);
	dto->transform.position = new_position;
	dto->transform.dots[0] = v3_add(dto->transform.dots[0], diff);
	dto->transform.dots[1] = v3_add(dto->transform.dots[1], diff);
	dto->transform.dots[2] = v3_add(dto->transform.dots[2], diff);
	while (++i < SECTION_CNT)
		dto->sections[i].position = v3_add(dto->sections[i].position, diff);
}

void		paste_shape(t_rt *rt)
{
	SHAPE	*shape;
	SHAPE	*temp;

	if (!rt->info->s_copy || rt->scene->s_cnt >= MAX_SHAPES_COUNT)
		return ;
	if (!(shape = (SHAPE*)malloc(sizeof(SHAPE))))
		ft_error("Can't allocate memory");
	get_default_shape(shape, rt->info->s_copy->dto);
	update_positions(shape->dto,
					v3_add(v3_add(rt->ocl->dto.cam.origin,
						v3_scale(rt->ocl->dto.cam.forward, 50)),
						v3_scale(rt->ocl->dto.cam.upguide, -1)));
	if (!(shape->name = ft_strdup(rt->info->s_copy->name)))
		ft_error("Can't allocate memory");
	if (rt->scene->shapes == NULL)
	{
		rt->scene->shapes = shape;
		return (new_shape_update_everything(rt, &rt->gtk->ui.shapes, shape));
	}
	temp = rt->scene->shapes;
	while (temp->next)
		temp = temp->next;
	temp->next = shape;
	shape->prev = temp;
	new_shape_update_everything(rt, &rt->gtk->ui.shapes, shape);
}
