/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 21:24:23 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/06 03:30:52 by cschoen          ###   ########lyon.fr   */
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

typedef struct	s_field
{
	char		*full_name;
	json_object	*obj;
}				t_field;

t_scene			jc_parse(const char *file_name);

t_field			jc_get_parsed_json(const char *file_name);
t_field			jc_get_field(const char *field_name, const t_field *parent,
																json_type type);
t_field			jc_get_nullable_field(const char *field_name,
										const t_field *parent, json_type type);
t_field			jc_get_field_idx(const int index, const t_field *parent,
																json_type type);
void			jc_clear_field(t_field *field);

json_object		*jc_get_obj_by_key(const char *key, const t_field *parent);

char			*jc_parent_dot_child(const char *parent, const char *child);
char			*jc_field_with_index(const char *field, const int index);

size_t			jc_get_array_length(const t_field *field);
float			jc_get_float(const t_field *parent, const char *child_name);
cl_float3		jc_get_cl_float3(const t_field *parent, const char *child_name);
t_color			jc_get_color(const t_field *parent, const char *child_name);
t_transform		jc_get_transform(const t_field *parent, const char *child_name);
t_material		jc_get_material(const t_field *parent, const char *child_name);
t_cam			jc_get_camera(const t_field *parent, const char *child_name);
t_list_shape	*jc_get_shape(const t_field *parent, const int index);
t_list_shape	*jc_get_shapes(const t_field *parent, const char *child_name);

#endif
