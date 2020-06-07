/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/20 22:42:43 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	init_size_of_arrays(JC_FIELD scene_field, SCENE *scene)
{
	scene->s_cnt = jc_get_array_length(jc_get_field(scene_field, "shapes",
													(JC_ARR | JC_NULL)));
	scene->l_cnt = jc_get_array_length(jc_get_field(scene_field, "lights",
													JC_ARR));
	scene->t_cnt = jc_get_array_length(jc_get_field(scene_field, "textures",
													JC_ARR | JC_NULL));
	scene->n_cnt = jc_get_array_length(jc_get_field(scene_field, "normal maps",
	JC_ARR | JC_NULL));
}

SCENE		*parse_scene(const char *file_name)
{
	JC_FIELD	json_field;
	JC_FIELD	scene_field;
	SCENE		*scene;

	if ((scene = (SCENE*)malloc(sizeof(SCENE))) == NULL)
		ft_error("Can't allocate memory");
	json_field = jc_get_json_field(file_name, PARSE_TEXT_SIZE);
	scene_field = jc_get_field(json_field, "scene", JC_OBJ);
	scene->cam = parse_camera(scene_field, "camera");
	scene->textures = parse_textures(scene_field, "textures");
	scene->normal_maps = parse_textures(scene_field, "normal maps");
	scene->shapes = parse_shapes(scene_field, "shapes", scene->textures, scene->normal_maps);
	scene->lights = parse_lights(scene_field, "lights");
	init_size_of_arrays(scene_field, scene);
	parse_settings(json_field, scene);
	jc_clear_all(json_field);
	return (scene);
}
