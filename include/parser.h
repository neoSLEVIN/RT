/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/23 01:53:23 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "jc_parser.h"
# include "scene.h"

# define PARSE_TEXT_SIZE 1200000
# define MAX_SHAPES_COUNT 1000
# define MAX_LIGHTS_COUNT 100
# define MAX_PPM_IMG_COUNT 20
/*
** ========================== Parse main Scene entity ==========================
*/
SCENE		*parse_scene(const char *file_name);
/*
** =============================== Parse camera ================================
*/
CAMERA		parse_camera(const JC_FIELD parent, const char *child_name);
/*
** ============================== Parse sections ===============================
*/
void		parse_sections(const JC_FIELD parent, const char *child_name,
						DTO_SHAPE *dto);
SECTION		parse_section_idx(const JC_FIELD parent, const size_t index,
						FLT3 dto_position);
_Bool		parse_section_style(const JC_FIELD parent, const char *child_name);
SHAPE_TYPE	parse_section_type(const JC_FIELD parent, const char *child_name);
void		init_default_shape_sections(DTO_SHAPE *dto);
/*
** ============================== Parse textures ===============================
*/
PPM_IMG		*parse_textures(const JC_FIELD parent, const char *child_name);
PPM_IMG		*parse_texture_idx(const JC_FIELD parent, const size_t index);
TEXTURE		parse_texture_info_in_shape(const JC_FIELD parent,
						const char *child_name, char **texture_name,
						PPM_IMG *textures);
int			check_for_texture_name(PPM_IMG *texture, const char *name,
						_Bool is_normal_map);
/*
** =============================== Parse shapes ================================
*/
SHAPE		*parse_shapes(const JC_FIELD parent, const char *child_name,
						PPM_IMG *textures, PPM_IMG *normal_maps);
SHAPE		*parse_shape_idx(const JC_FIELD parent, const size_t index,
						PPM_IMG *textures, PPM_IMG *normal_maps);
SHAPE_TYPE	parse_shape_type(const JC_FIELD parent, const char *child_name);
FLT3		parse_shape_param_by_type(const JC_FIELD shape_field,
						SHAPE_TYPE type);
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
MATERIAL	parse_material(const JC_FIELD parent, const char *child_name);
/*
** ================================ Send error =================================
*/
void		parse_error(const char *parent_name, const char *child_name,
						const char *cause);
/*
** =================================== Utils ===================================
*/
char		*unnamed_obj(size_t index, char *prefix);
void		check_reserved_names(const JC_FIELD texture_field,
								const char *name, _Bool is_normal_maps);
int			get_reserved_name_index(const char *name, _Bool is_normal_maps);

#endif
