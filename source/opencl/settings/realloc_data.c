/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 02:21:39 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/17 03:57:28 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

void	realloc_shapes_dto(DTO_SHAPE **dto, SHAPE *shape, int cnt)
{
	DTO_SHAPE	*temp;
	int			i;

	if (!dto || !(*dto))
		ft_error("NPE: realloc_shapes_dto");
	temp = *dto;
	if (!(*dto = (DTO_SHAPE*)malloc(sizeof(DTO_SHAPE) * cnt)))
		ft_error("Can't allocate memory");
	i = -1;
	while (++i < cnt && shape)
	{
		(*dto)[i] = *shape->dto;
		shape->dto = &(*dto)[i];
		shape = shape->next;
	}
	ft_memdel((void**)&temp);
}

void	realloc_lights_dto(DTO_LIGHT **dto, LIGHT *light, int cnt)
{
	DTO_LIGHT	*temp;
	int			i;

	if (!dto || !(*dto))
		ft_error("NPE: realloc_lights_dto");
	temp = *dto;
	if (!(*dto = (DTO_LIGHT*)malloc(sizeof(DTO_LIGHT) * cnt)))
		ft_error("Can't allocate memory");
	i = -1;
	while (++i < cnt && light)
	{
		(*dto)[i] = *light->dto;
		light->dto = &(*dto)[i];
		light = light->next;
	}
	ft_memdel((void**)&temp);
}
