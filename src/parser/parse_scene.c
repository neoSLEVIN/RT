/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 01:12:12 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/03 04:08:52 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	g_uid = 0;

//t_shape_type	jc_get_shape_type(const t_jc_field *parent, const char *child_name)
//{
//	t_jc_field			type_field;
//	const char		*str_type;
//	t_shape_type	type;
//
//	type_field = jc_get_field(child_name, parent, json_type_string);
//	str_type = json_object_get_string(type_field.obj);
//	if (ft_strequ(str_type, "PLANE"))
//		type = PLANE;
//	else if (ft_strequ(str_type, "SPHERE"))
//		type = SPHERE;
//	else if (ft_strequ(str_type, "CYLINDER"))
//		type = CYLINDER;
//	else if (ft_strequ(str_type, "CONE"))
//		type = CONE;
//	else
//	{
//		ft_printf("Error:\tUndefined type of shape: %s\n\t%s%s\n",
//			type_field.full_name, "Valid types are: ",
//			"[\"PLANE\", \"SPHERE\", \"CYLINDER\", \"CONE\"]");
//		exit(1);
//	}
//	jc_clear_field(&type_field);
//	return (type);
//}
//
//t_list_shape	*jc_get_shape(const t_jc_field *parent, const int index)
//{
//	t_jc_field			shape_field;
//	t_list_shape	*shape;
//
//	shape_field = jc_get_field_idx(index, parent, json_type_object);
//	if(!(shape = (t_list_shape*)malloc(sizeof(t_list_shape)))) {
//		ft_error("Can't allocate memory in parsing");
//	}
//	shape->uid = g_uid++;
//	shape->marker = FALSE;
//	shape->next = NULL;
//	shape->type = jc_get_shape_type(&shape_field, "type");
////	shape->shape = (void *)jc_get_shape_fields_by_type()
//	jc_clear_field(&shape_field);
//	return (shape);
//}

static t_scene	scene_init(void)
{
	t_scene	scene;

	// TODO scene.cam =
	scene.shapes = NULL;
	scene.lights = NULL;
	return (scene);
}

t_scene	parse_scene(const char *file_name)
{
	t_jc_field	json_field;
	t_jc_field	scene_field;
	t_scene		scene;

	scene = scene_init();
	json_field = jc_get_json_field(file_name, PARSE_TEXT_SIZE);
	scene_field = jc_get_field("scene", &json_field, JC_OBJ);
//	scene.cam = jc_get_camera(&scene_field, "camera");
//	scene.shapes = jc_get_shapes(&scene_field, "shapes");
//	// TODO scene.lights = jc_get_lights(&scene_field, "lights");
	t_material	del = parse_material(&scene_field, "del");
	ft_printf("%d\t%d\t%d\n%f\n",
		del.color.r, del.color.g, del.color.b, del.specular);
	t_transform	del2 = parse_transform(&scene_field, "del2");
	ft_printf("%f\t%f\t%f\n%f\t%f\t%f\n%f\t%f\t%f\n",
			del2.direction.x, del2.direction.y, del2.direction.z,
			del2.rotation.x, del2.rotation.y, del2.rotation.z,
			del2.position.x, del2.position.y, del2.position.z);
	jc_clear_field(&scene_field);
	jc_clear_json_field(&json_field);
//	while (scene.shapes != NULL)
//	{
//		if (scene.shapes->type == PLANE)
//			ft_printf("%d\n", scene.shapes->uid);
//		scene.shapes = scene.shapes->next;
//	}
	return (scene);
}
