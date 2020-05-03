/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 21:24:23 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/03 04:04:12 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

# include "jc_parser.h"
# include "scene.h"

# define PARSE_TEXT_SIZE 12000

t_scene			parse_scene(const char *file_name);

t_color			parse_color(const t_jc_field *parent, const char *child_name);
t_transform		parse_transform(const t_jc_field *parent,
								const char *child_name);
t_material		parse_material(const t_jc_field *parent,
								const char *child_name);
t_cam			jc_get_camera(const t_jc_field *parent, const char *child_name);
t_list_shape	*jc_get_shape(const t_jc_field *parent, const int index);
t_list_shape	*jc_get_shapes(const t_jc_field *parent, const char *child_name);

#endif
