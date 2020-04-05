/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 21:24:23 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/05 06:07:34 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

#include "libft.h"
#include "scene.h"
#include <json-c/json.h>

# define PARSE_TEXT_SIZE 12000
# define MAX_FLOAT 1.0e+9
# define MIN_FLOAT 1.0e-9

t_scene		parse(char *file_name);

char		*parent_dot_child(const char *parent, const char *child);

json_object	*get_parsed_json(char *file_name);
json_object	*get_obj_by_key(char *key, const json_object *parent);

float		get_float_by_obj(const json_object *obj, const char *field_name);
t_vec3		get_vec3_by_obj(const json_object *obj, const char *parent_name);
t_color		get_color_by_obj(json_object *obj, const char *field_name);
t_transform	get_transform_by_obj(const json_object *obj,
								const char *parent_name);
t_material	get_material_by_obj(const json_object *obj,
								const char *parent_name);

#endif
