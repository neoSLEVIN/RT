/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

void	translate_cam(DTO_CAM *dto, CAMERA *cam)
{
	dto->upguide = (FLT3){0.0f, 1.0f, 0.0f};
	dto->origin = cam->transform.position;
	dto->target = cam->transform.direction;
	dto->forward = v3_sub(dto->target, dto->origin);
	dto->forward = v3_norm(dto->forward);
	dto->right = v3_cross(dto->forward, dto->upguide);
	if (v3_length(dto->right) < 0.0000001f)
		dto->right = v3_cross(dto->forward, (FLT3){1.0f, 0.0f, 0.0f});
	dto->right = v3_norm(dto->right);
	dto->up = v3_cross(dto->right, dto->forward);
}

void	translate_shapes(DTO_SHAPE **dto, SHAPE *shape, int cnt)
{
	int	i;

	if (!dto)
		ft_error("NPE: translate_shapes");
	if (*dto)
		ft_memdel((void**)dto);
	if (!(*dto = (DTO_SHAPE*)malloc(sizeof(DTO_SHAPE) * cnt)))
		ft_error("Can't allocate memory");
	i = -1;
	while (++i < cnt && shape)
	{
		(*dto)[i] = shape->dto;
		shape = shape->next;
	}
}

void	translate_lights(DTO_LIGHT **dto, LIGHT *light, int cnt)
{
	int	i;

	if (!dto)
		ft_error("NPE: translate_lights");
	if (*dto)
		ft_memdel((void**)dto);
	if (!(*dto = (DTO_LIGHT*)malloc(sizeof(DTO_LIGHT) * cnt)))
		ft_error("Can't allocate memory");
	i = -1;
	while (++i < cnt && light)
	{
		(*dto)[i] = light->dto;
		light = light->next;
	}
}
