/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 01:12:12 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/06 02:39:09 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	init_options(t_scene *scene, JC_FIELD *scene_field)
{
	scene->s_cnt = jc_get_array_length(jc_get_field("shapes", *scene_field,
									(JC_ARR | JC_NULL)));
	scene->l_cnt = jc_get_array_length(jc_get_field("lights", *scene_field,
									JC_ARR));
	scene->s_marker = NULL;
	scene->l_marker = NULL;
}

t_scene		*parse_scene(const char *file_name)
{
	JC_FIELD	json_field;
	JC_FIELD	scene_field;
	t_scene		*scene;

	if ((scene = (t_scene*)malloc(sizeof(t_scene))) == NULL)
		ft_error("Can't allocate memory");
	json_field = jc_get_json_field(file_name, PARSE_TEXT_SIZE);
	scene_field = jc_get_field("scene", json_field, JC_OBJ);
	scene->cam = parse_camera(scene_field, "camera");
	scene->shapes = parse_shapes(scene_field, "shapes");
	scene->lights = parse_lights(scene_field, "lights");
	init_options(scene, &scene_field);
	jc_clear_all(json_field);
	return (scene);
}
