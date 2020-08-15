#include "gtk_module.h"

void	init_default_shape_dto(DTO_CAM *cam, DTO_SHAPE *dto)
{
	dto->type = SPHERE;
	dto->transform.position =
		v3_add(cam->origin, v3_scale(cam->forward, 10));
	dto->transform.direction = cam->upguide;
	dto->transform.rotation = (FLT3){0.0f, 0.0f, 0.0f};
	dto->material.transparency = 0.0f;
	dto->material.specular = 0.05f;
	dto->material.reflective = 0.235f;
	dto->material.color = (FLT3){0.52f, 0.88f, 0.96f};
	dto->texture.id = -1;
	dto->texture.rotation = 0.0f;
	dto->texture.direction = dto->transform.direction;
	dto->normal_map.id = -1;
	dto->normal_map.rotation = 0.0f;
	dto->normal_map.direction = dto->transform.direction;
	dto->params = (FLT3){0.5f, 0.5f, 0.0f};
	dto->marker = FALSE;
	init_default_shape_sections(dto);
}
