/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/21 04:45:10 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

# include "jc_parser.h"
# include "scene.h"

# define PARSE_TEXT_SIZE 12000
/*
** ========================== Parse main Scene entity ==========================
*/
SCENE		*parse_scene(const char *file_name);
/*
** =============================== Parse camera ================================
*/
CAMERA		parse_camera(const JC_FIELD parent, const char *child_name);
/*
** ============================== Parse textures ===============================
*/
TEXTURE		*parse_textures(const JC_FIELD parent, const char *child_name);
TEXTURE		*parse_texture_idx(const JC_FIELD parent, const size_t index);
int			check_for_texture_name(TEXTURE *texture, const char *name);
/*
** =============================== Parse shapes ================================
*/
SHAPE		*parse_shapes(const JC_FIELD parent, const char *child_name,
						TEXTURE *textures);
SHAPE		*parse_shape_idx(const JC_FIELD parent, const size_t index,
						TEXTURE *textures);
SHAPE_TYPE	parse_shape_type(const JC_FIELD parent, const char *child_name);
/*
** =============================== Parse lights ================================
*/
LIGHT		*parse_lights(const JC_FIELD parent, const char *child_name);
LIGHT		*parse_light_idx(const JC_FIELD parent, const size_t index);
LIGHT_TYPE	parse_light_type(const JC_FIELD parent, const char *child_name);
/*
** ============================== Parse settings ===============================
*/
void		parse_settings(JC_FIELD json_field, SCENE *scene);
/*
** ========================= Parse additional entities =========================
*/
FLT3		parse_cl_float3(const JC_FIELD parent, const char *child_name);
FLT3		parse_cl_float3_or_default(const JC_FIELD parent,
						const char *child_name, FLT3 default_value);
FLT3		parse_color(const JC_FIELD parent, const char *child_name);
FLT3		parse_color_or_default(const JC_FIELD parent,
								const char *child_name, char *default_color);
TRANSFORM	parse_transform(const JC_FIELD parent, const char *child_name);
MATERIAL	parse_material(const JC_FIELD parent, const char *child_name,
						char **texture_name, TEXTURE *textures);
/*
** ================================ Send error =================================
*/
void		parse_error(const char *parent_name, const char *child_name,
						const char *cause);

#endif
