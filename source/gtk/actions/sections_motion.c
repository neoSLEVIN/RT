#include "gtk_module.h"

void	move_sections_by_camera_movement(DTO_SHAPE *dto, DTO_CAM *cam,
										guint key)
{
	int		i;
	FLT3	*section_pos;

	i = -1;
	while (++i < SECTION_CNT)
	{
		section_pos = &dto->sections[i].position;
		if (key == GDK_KEY_space)
			*section_pos = v3_add(*section_pos, v3_scale(cam->upguide, STEP));
		else if (key == GDK_KEY_c)
			*section_pos = v3_sub(*section_pos, v3_scale(cam->upguide, STEP));
		else if (key == GDK_KEY_w)
			*section_pos = v3_add(*section_pos,
				v3_scale(cam->forward, STEP * 2));
		else if (key == GDK_KEY_s)
			*section_pos = v3_sub(*section_pos,
				v3_scale(cam->forward, STEP * 2));
		else if (key == GDK_KEY_d)
			*section_pos = v3_add(*section_pos, v3_scale(cam->right, STEP));
		else if (key == GDK_KEY_a)
			*section_pos = v3_sub(*section_pos, v3_scale(cam->right, STEP));
	}
}

void	move_sections_by_mouse(FLT3 diff, SECTION *sections)
{
	int	i;

	i = -1;
	while (++i < SECTION_CNT)
		sections[i].position = v3_add(sections[i].position, diff);
}

void	rotate_sections(DTO_SHAPE *dto, DTO_CAM *cam, cl_float angle,
						guint key)
{
	int			i;
	FLT3		sec_target;
	SECTION		*sections;
	cl_float	len;

	i = -1;
	sections = dto->sections;
	while (++i < SECTION_CNT)
	{
		sec_target = v3_sub(sections[i].position, dto->transform.position);
		len = v3_length(v3_sub(sections[i].position, dto->transform.position));
		if ((key == GDK_KEY_k || key == GDK_KEY_i) && len > 0.01f)
			sec_target = v3_rot_v(sec_target, cam->right, angle);
		else if ((key == GDK_KEY_j || key == GDK_KEY_l) && len > 0.01f)
			sec_target = v3_rot_v(sec_target, cam->upguide, angle);
		else if ((key == GDK_KEY_u || key == GDK_KEY_o) && len > 0.01f)
			sec_target = v3_rot_v(sec_target, cam->forward, angle);
		if (key == GDK_KEY_k || key == GDK_KEY_i)
			sections[i].direction = v3_rot_v(sections[i].direction, cam->right, angle);
		else if (key == GDK_KEY_j || key == GDK_KEY_l)
			sections[i].direction = v3_rot_v(sections[i].direction, cam->upguide, angle);
		else if (key == GDK_KEY_u || key == GDK_KEY_o)
			sections[i].direction = v3_rot_v(sections[i].direction, cam->forward, angle);
		sections[i].position = v3_add(dto->transform.position, sec_target);
	}
}
