/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_default_shape_dto.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:28:30 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:28:31 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	init_default_dots(FLT3 *pos, FLT3 *dots, DTO_CAM *cam)
{
	dots[0] = v3_add(*pos, cam->right);
	dots[1] = v3_add(*pos, cam->upguide);
	dots[2] = v3_sub(v3_sub(v3_scale(*pos, 3.0f), dots[0]), dots[1]);
}

void		init_default_shape_dto(DTO_CAM *cam, DTO_SHAPE *dto)
{
	dto->type = SPHERE;
	dto->transform.position =
		v3_add(v3_add(cam->origin, v3_scale(cam->forward, 10)),
				v3_scale(cam->upguide, -0.01f));
	dto->transform.direction = v3_rot_v(cam->upguide, cam->right, RAD);
	dto->transform.rotation = cam->right;
	dto->transform.angle = 0;
	init_default_dots(&dto->transform.position, dto->transform.dots, cam);
	dto->material.transparency = 0.0f;
	dto->material.refraction = 0.0f;
	dto->material.specular = 0.05f;
	dto->material.reflective = 0.235f;
	dto->material.color = (FLT3){0.52f, 0.88f, 0.96f};
	dto->texture.id = -1;
	dto->texture.rotation = 0.0f;
	dto->texture.direction = dto->transform.direction;
	dto->normal_map.id = -1;
	dto->normal_map.rotation = 0.0f;
	dto->normal_map.direction = dto->transform.direction;
	dto->params = (FLT3){0.5f, 0.5f, 0.5f};
	dto->marker = FALSE;
	init_default_shape_sections(dto);
}
