/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections_motion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:22:30 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:22:30 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void			move_sections_by_camera_movement(DTO_SHAPE *dto, DTO_CAM *cam,
										guint key, cl_float step)
{
	int			i;
	FLT3		*section_pos;

	i = -1;
	while (++i < SECTION_CNT)
	{
		section_pos = &dto->sections[i].position;
		if (key == GDK_KEY_space)
			*section_pos = v3_add(*section_pos, v3_scale(cam->upguide, step));
		else if (key == GDK_KEY_c)
			*section_pos = v3_sub(*section_pos, v3_scale(cam->upguide, step));
		else if (key == GDK_KEY_w)
			*section_pos = v3_add(*section_pos,
				v3_scale(cam->forward, step * 2));
		else if (key == GDK_KEY_s)
			*section_pos = v3_sub(*section_pos,
				v3_scale(cam->forward, step * 2));
		else if (key == GDK_KEY_d)
			*section_pos = v3_add(*section_pos, v3_scale(cam->right, step));
		else if (key == GDK_KEY_a)
			*section_pos = v3_sub(*section_pos, v3_scale(cam->right, step));
	}
}

void			move_sections_by_mouse(FLT3 diff, SECTION *sections)
{
	int			i;

	i = -1;
	while (++i < SECTION_CNT)
		sections[i].position = v3_add(sections[i].position, diff);
}

static void		change_section_direction(FLT3 *direction, DTO_CAM *cam,
									cl_float angle, guint key)
{
	if (key == GDK_KEY_k || key == GDK_KEY_i)
		*direction = v3_rot_v(*direction, cam->right, angle);
	else if (key == GDK_KEY_j || key == GDK_KEY_l)
		*direction = v3_rot_v(*direction, cam->upguide, angle);
	else if (key == GDK_KEY_u || key == GDK_KEY_o)
		*direction = v3_rot_v(*direction, cam->forward, angle);
}

void			rotate_sections(DTO_SHAPE *dto, DTO_CAM *cam, cl_float angle,
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
		change_section_direction(&sections[i].direction, cam, angle, key);
		sections[i].position = v3_add(dto->transform.position, sec_target);
	}
}
