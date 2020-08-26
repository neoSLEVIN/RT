/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/18 23:11:46 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	parse_display_error(const JC_FIELD display_field,
						const char *str_index, const char *name, INT2 min_max)
{
	ft_printf("Error:\t\"%s%s\": Display %s must be in range [%d; %d]\n",
		jc_full_name(display_field), str_index, name, min_max.x, min_max.y);
	exit(1);
}

static INT2	parse_display_or_default(const JC_FIELD parent,
									const char *child_name, INT2 default_value)
{
	JC_FIELD	display_field;
	INT2		display;

	display_field = jc_get_field(parent, child_name, (JC_ARR | JC_NULL));
	if (jc_is_null(display_field))
		return (default_value);
	if (jc_get_array_length(display_field) != 2)
		parse_error(jc_full_name(display_field), NULL,
			"Field must be an array and have only two number elements");
	display.x = (int)jc_get_float_idx(display_field, 0);
	if (display.x < MIN_WIDTH || display.x > COLS)
		parse_display_error(display_field, "[0]",
							"width", (INT2){MIN_WIDTH, COLS});
	display.y = (int)jc_get_float_idx(display_field, 1);
	if (display.y < MIN_HEIGHT || display.y > ROWS)
		parse_display_error(display_field, "[1]",
							"height", (INT2){MIN_HEIGHT, ROWS});
	return (display);
}

CAMERA		parse_camera(const JC_FIELD parent, const char *child_name)
{
	JC_FIELD	cam_field;
	CAMERA		cam;

	cam_field = jc_get_field(parent, child_name, JC_OBJ);
	cam.dto = NULL;
	cam.position = parse_cl_float3(cam_field, "position");
	cam.direction = parse_cl_float3_or_default(cam_field, "direction",
					(FLT3){0.0f, 0.0f, 1.0f});
	cam.direction = v3_norm(cam.direction);
	if (v3_length(cam.direction) == 0.0f)
		parse_error(jc_full_name(cam_field), "direction",
					"The vector must not be a zero vector.");
	cam.rotation = jc_get_float_or_default(cam_field, "rotation", 0.0f);
	cam.rotation = deg_to_rad(cam.rotation);
	cam.fov = jc_get_float_or_default(cam_field, "fov", 25.0f);
	if (cam.fov < 10.0f || cam.fov > 160.0f)
		parse_error(jc_full_name(cam_field), "fov",
					"Value must be in range [10; 160].");
	cam.display =
		parse_display_or_default(cam_field, "display", (INT2){COLS, ROWS});
	cam.fps = jc_get_float_or_default(cam_field, "fps", 25);
	if (cam.fps < 1 || cam.fps > 80)
		parse_error(jc_full_name(cam_field), "fps",
					"Value must be in range [1; 80]");
	return (cam);
}
