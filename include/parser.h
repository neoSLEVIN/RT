/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 21:24:23 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/06 02:40:03 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

# include "jc_parser.h"
# include "scene.h"

# define PARSE_TEXT_SIZE 12000
/*
** ================================ Main entity ================================
*/
t_scene		*parse_scene(const char *file_name);
/*
** =============================== Parse camera ================================
*/
t_cam		parse_camera(const JC_FIELD parent, const char *child_name);
/*
** =============================== Parse shapes ================================
*/
SHAPE		*parse_shapes(const JC_FIELD parent, const char *child_name);
SHAPE		*parse_shape_idx(const JC_FIELD parent, const int index);
SHAPE_TYPE	parse_shape_type(const JC_FIELD parent, const char *child_name);
/*
** =============================== Parse lights ================================
*/
LIGHT		*parse_lights(const JC_FIELD parent, const char *child_name);
LIGHT		*parse_light_idx(const JC_FIELD parent, const int index);
LIGHT_TYPE	parse_light_type(const JC_FIELD parent, const char *child_name);
/*
** ========================= Parse additional entities =========================
*/
FLT3		parse_cl_float3(const JC_FIELD parent, const char *child_name);
FLT3		parse_color(const JC_FIELD parent, const char *child_name);
t_transform	parse_transform(const JC_FIELD parent, const char *child_name);
t_material	parse_material(const JC_FIELD parent, const char *child_name);
/*
** ================================ Send error =================================
*/
void		parse_error(const char *parent_name, const char *child_name,
						const char *cause);

FLT3	v3_norm(FLT3 v);

#endif
