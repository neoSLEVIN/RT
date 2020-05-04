/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 01:12:12 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/04 20:57:03 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	init_options(t_options *options)
{
	options->l_marker = NULL;
	options->s_marker = NULL;
	options->mouse_x = -1;
	options->mouse_y = -1;
}

t_scene		*parse_scene(const char *file_name)
{
	JC_FIELD	json_field;
	JC_FIELD	scene_field;
	t_scene		*scene;

	g_uid = 0;
	if ((scene = (t_scene*)malloc(sizeof(t_scene))) == NULL)
		ft_error("Can't allocate memory");
	json_field = jc_get_json_field(file_name, PARSE_TEXT_SIZE);
	scene_field = jc_get_field("scene", json_field, JC_OBJ);
	scene->cam = parse_camera(scene_field, "camera");
	scene->shapes = parse_shapes(scene_field, "shapes");
	scene->lights = parse_lights(scene_field, "lights");
	init_options(&scene->options);
	jc_clear_all(json_field);
	return (scene);
}
