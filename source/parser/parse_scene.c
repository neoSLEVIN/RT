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

static void	parse_max_size_error(const char *parent_name,
								const char *child_name, int size)
{
	ft_printf("Error:\t\"%s.%s\": Max size %d\n",
			parent_name, child_name, size);
	exit(1);
}

static void	init_size_of_arrays(JC_FIELD scene_field, SCENE *scene)
{
	scene->s_cnt = jc_get_array_length(jc_get_field(scene_field,
									"shapes", (JC_ARR | JC_NULL)));
	if (scene->s_cnt > MAX_SHAPES_COUNT)
		parse_max_size_error(jc_full_name(scene_field), "shapes",
			MAX_SHAPES_COUNT);
	scene->l_cnt = jc_get_array_length(jc_get_field(scene_field,
									"lights", JC_ARR));
	if (scene->l_cnt > MAX_LIGHTS_COUNT)
		parse_max_size_error(jc_full_name(scene_field), "lights",
			MAX_LIGHTS_COUNT);
	scene->t_cnt = jc_get_array_length(jc_get_field(scene_field,
									"textures", (JC_ARR | JC_NULL)));
	if (scene->t_cnt > MAX_PPM_IMG_COUNT)
		parse_max_size_error(jc_full_name(scene_field), "textures",
			MAX_PPM_IMG_COUNT);
	scene->n_cnt = jc_get_array_length(jc_get_field(scene_field,
									"normal maps", (JC_ARR | JC_NULL)));
	if (scene->n_cnt > MAX_PPM_IMG_COUNT)
		parse_max_size_error(jc_full_name(scene_field), "normal maps",
			MAX_PPM_IMG_COUNT);
}

static void	init_default_off(t_off *off)
{
	off->filename = NULL;
	off->points = NULL;
	off->faces = NULL;
	off->colors = NULL;
	off->p_cnt = 0;
	off->f_cnt = 0;
	off->err = NULL;
	off->line = NULL;
	off->list = NULL;
	off->open_fd = FALSE;
	off->fd = -1;
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
	init_size_of_arrays(scene_field, scene);
	init_default_off(&scene->off);
	scene->cam = parse_camera(scene_field, "camera");
	scene->textures = parse_textures(scene_field, "textures");
	scene->normal_maps = parse_textures(scene_field, "normal maps");
	scene->shapes = parse_shapes(scene_field, "shapes", scene);
	scene->lights = parse_lights(scene_field, "lights");
	parse_settings(json_field, scene);
	jc_clear_all(json_field);
	return (scene);
}
