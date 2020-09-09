/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_default_shape.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:28:27 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:28:27 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

SHAPE	*get_default_shape(SHAPE *shape, DTO_SHAPE *dto)
{
	shape->tree_iter = NULL;
	shape->name = NULL;
	shape->next = NULL;
	shape->prev = NULL;
	shape->texture_name = NULL;
	shape->normal_map_name = NULL;
	shape->dto = dto;
	return (shape);
}
