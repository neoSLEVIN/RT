/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 01:12:12 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/06 05:41:57 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	g_uid = 0;

t_shape_type	jc_get_shape_type(const t_field *parent, const char *child_name)
{
	t_field			type_field;
	const char		*str_type;
	t_shape_type	type;

	type_field = jc_get_field(child_name, parent, json_type_string);
	str_type = json_object_get_string(type_field.obj);
	if (ft_strequ(str_type, "PLANE"))
		type = PLANE;
	else if (ft_strequ(str_type, "SPHERE"))
		type = SPHERE;
	else if (ft_strequ(str_type, "CYLINDER"))
		type = CYLINDER;
	else if (ft_strequ(str_type, "CONE"))
		type = CONE;
	else
	{
		ft_printf("Error:\tUndefined type of shape: %s\n\t%s%s\n",
			type_field.full_name, "Valid types are: ",
			"[\"PLANE\", \"SPHERE\", \"CYLINDER\", \"CONE\"]");
		exit(1);
	}
	jc_clear_field(&type_field);
	return (type);
}

t_list_shape	*jc_get_shape(const t_field *parent, const int index)
{
	t_field			shape_field;
	t_list_shape	*shape;

	shape_field = jc_get_field_idx(index, parent, json_type_object);
	if(!(shape = (t_list_shape*)malloc(sizeof(t_list_shape)))) {
		ft_error("Can't allocate memory in parsing");
	}
	shape->uid = g_uid++;
	shape->marker = FALSE;
	shape->next = NULL;
	shape->type = jc_get_shape_type(&shape_field, "type");
//	shape->shape = (void *)jc_get_shape_fields_by_type()
	jc_clear_field(&shape_field);
	return (shape);
}

t_scene	jc_parse(const char *file_name)
{
	t_field		parsed_json;
	t_field		scene_field;
	t_scene		scene;

	parsed_json = jc_get_parsed_json(file_name);
	scene_field = jc_get_field("scene", &parsed_json, json_type_object);
	scene.cam = jc_get_camera(&scene_field, "camera");
	scene.shapes = jc_get_shapes(&scene_field, "shapes");
	// TODO scene.lights = jc_get_lights(&scene_field, "lights");
	jc_clear_field(&scene_field);
	jc_clear_field(&parsed_json);
	while (scene.shapes != NULL)
	{
		if (scene.shapes->type == PLANE)
			ft_printf("%d\n", scene.shapes->uid);
		scene.shapes = scene.shapes->next;
	}
	return (scene);
}
