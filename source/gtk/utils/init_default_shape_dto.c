#include "gtk_module.h"

static void	init_default_dots(FLT3 *pos, FLT3 *dots)
{
	FLT3	two_dots_sum;

	two_dots_sum = v3_sub(v3_scale(*pos, 3.0f), dots[0]);
	dots[1] = (FLT3){two_dots_sum.x, two_dots_sum.y, 0.0f};
	dots[2] = (FLT3){0.0f, 0.0f, two_dots_sum.z};
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
	dto->params[0] = (FLT3){0.5f, 0.5f, 0.0f};
	init_default_dots(&dto->transform.position, dto->params);
	dto->marker = FALSE;
	init_default_shape_sections(dto);
}
