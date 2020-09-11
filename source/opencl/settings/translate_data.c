/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/21 02:59:50 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

void	translate_off(t_dto *dto, t_off *off)
{
	if (!off->points)
	{
		if (!(off->points = (FLT3*)malloc(sizeof(FLT3))))
			ft_error("Can't allocate memory");
	}
	dto->points = off->points;
	if (!off->colors)
	{
		if (!(off->colors = (FLT3*)malloc(sizeof(FLT3))))
			ft_error("Can't allocate memory");
	}
	dto->colors = off->colors;
	if (!off->faces)
	{
		if (!(off->faces = (cl_int3*)malloc(sizeof(cl_int3))))
			ft_error("Can't allocate memory");
	}
	dto->faces = off->faces;
}

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
}

void	translate_textures(DTO_PPM_IMG **dto, PPM_IMG *texture, int cnt)
{
	int			i;
	DTO_PPM_IMG	*temp;

	if (!dto)
		ft_error("NPE: translate_textures");
	if (*dto)
		ft_error("Can't translate memory to existing shapes dto");
	if (!(*dto = (DTO_PPM_IMG*)malloc(sizeof(DTO_PPM_IMG) * cnt)))
		ft_error("Can't allocate memory");
	i = -1;
	while (++i < cnt && texture)
	{
		temp = read_ppm(texture->path);
		(*dto)[i] = *temp;
		texture->dto = &(*dto)[i];
		ft_memdel((void**)&temp);
		texture = texture->next;
	}
}

void	translate_shapes(DTO_SHAPE **dto, SHAPE *shape, int cnt)
{
	int	i;
	int	alloc_size;

	if (!dto)
		ft_error("NPE: translate_shapes");
	if (*dto)
		ft_error("Can't translate memory to existing shapes dto");
	alloc_size = (cnt == 0) ? 1 : cnt;
	if (!(*dto = (DTO_SHAPE*)malloc(sizeof(DTO_SHAPE) * alloc_size)))
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
