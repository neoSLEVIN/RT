/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/10 04:25:44 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	init_size_of_arrays(SCENE *scene, JC_FIELD scene_field)
{
	scene->s_cnt = jc_get_array_length(jc_get_field("shapes", scene_field,
									(JC_ARR | JC_NULL)));
	scene->l_cnt = jc_get_array_length(jc_get_field("lights", scene_field,
									JC_ARR));
}

static void	parse_settings(SCENE *scene, JC_FIELD json_field)
{
	JC_FIELD	settings_field;

	settings_field = jc_get_field("settings", json_field, (JC_OBJ | JC_NULL));
	if (jc_is_null(settings_field))
		return ;
	scene->fps = jc_get_float_or_default(settings_field, "fps", 25);
	if (scene->fps < 0.5 || scene->fps > 200)
		parse_error(jc_full_name(settings_field), "fps",
			" Value must be in range [0.5; 200.0].");
}

SCENE		*parse_scene(const char *file_name)
{
	JC_FIELD	json_field;
	JC_FIELD	scene_field;
	SCENE		*scene;

	if ((scene = (SCENE*)malloc(sizeof(SCENE))) == NULL)
		ft_error("Can't allocate memory");
	json_field = jc_get_json_field(file_name, PARSE_TEXT_SIZE);
	scene_field = jc_get_field("scene", json_field, JC_OBJ);
	scene->cam = parse_camera(scene_field, "camera");
	scene->shapes = parse_shapes(scene_field, "shapes");
	scene->lights = parse_lights(scene_field, "lights");
	init_size_of_arrays(scene, scene_field);
	parse_settings(scene, json_field);
	jc_clear_all(json_field);
	return (scene);
}
