/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/17 02:14:11 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

void	translate_cam(DTO_CAM *dto, CAMERA *cam)
{
	cl_float	rot_y;
	cl_float	*angle;

	dto->origin = cam->position;
	dto->forward = v3_norm(cam->direction);
	dto->target = v3_add(dto->origin, dto->forward);
	angle = &cam->rotation;
	rot_y = atan2f(dto->forward.x, dto->forward.z);
	dto->right = (FLT3){-1.0f, 0.0f, 0.0f};
	dto->right = v3_rot_y(dto->right, rot_y);
	dto->right = v3_rot_v(dto->right, dto->forward, -(*angle));
	dto->up = v3_cross(dto->right, dto->forward);
	dto->upguide = v3_norm(dto->up);
	cam->dto = dto;
}

void	translate_shapes(DTO_SHAPE **dto, SHAPE *shape, int cnt)
{
	int	i;

	if (!dto)
		ft_error("NPE: translate_shapes");
	if (*dto)
		ft_error("Can't translate memory to existing shapes dto");
	if (!(*dto = (DTO_SHAPE*)malloc(sizeof(DTO_SHAPE) * cnt)))
		ft_error("Can't allocate memory");
	i = -1;
	while (++i < cnt && shape)
	{
		(*dto)[i] = *shape->dto;
		ft_memdel((void**)&shape->dto);
		shape->dto = &(*dto)[i];
		shape = shape->next;
	}
}

void	translate_lights(DTO_LIGHT **dto, LIGHT *light, int cnt)
{
	int	i;

	if (!dto)
		ft_error("NPE: translate_lights");
	if (*dto)
		ft_error("Can't translate memory to existing lights dto");
	if (!(*dto = (DTO_LIGHT*)malloc(sizeof(DTO_LIGHT) * cnt)))
		ft_error("Can't allocate memory");
	i = -1;
	while (++i < cnt && light)
	{
		(*dto)[i] = *light->dto;
		ft_memdel((void**)&light->dto);
		light->dto = &(*dto)[i];
		light = light->next;
	}
}
