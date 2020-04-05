/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 01:12:12 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/05 06:07:34 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static json_object	*get_obj_by_query(char *query, const json_object *parent)
{
	char		**split;
	char		**elem;
	json_object	*obj;

	if (!query || !(split = ft_strsplit(query, '.')))
		ft_error("Bad query for field");
	elem = split;
	obj = (json_object*)parent;
	while (*elem)
	{
		obj = get_obj_by_key(*elem, obj);
		++elem;
	}
	ft_strsplit_del(split);
	return (obj);
}

static t_cam	get_cam_by_obj()
{
	t_cam	cam;
	// TODO
	return (cam);
}

t_scene	parse(char *file_name)
{
	t_scene		scene;
	json_object	*parsed_json;

	parsed_json = get_parsed_json(file_name);
	scene.cam = get_cam_by_obj();
	t_transform	trans = get_transform_by_obj(get_obj_by_key("transform", parsed_json), "transform");
	ft_printf("%.15f %.15f %.15f\n%.15f %.15f %.15f\n",
			trans.position.x, trans.position.y, trans.position.z,
			trans.rotation.x, trans.rotation.y, trans.rotation.z);
	t_material	material = get_material_by_obj(get_obj_by_key("material", parsed_json), "material");
	ft_printf("%d %d %d\n%.15f\n",
			  material.color.r, material.color.g, material.color.b,
			  material.specular);
	return (scene);
}
