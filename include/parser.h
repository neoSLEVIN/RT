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
						SCENE *scene);
SHAPE		*parse_shape_idx(const JC_FIELD parent, const size_t index,
						SCENE *scene);
SHAPE_TYPE	parse_shape_type(const JC_FIELD parent, const char *child_name);
void		parse_shape_param_by_type(const JC_FIELD shape_field,
						SHAPE_TYPE type, FLT3 *params);
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
TRANSFORM	parse_transform(const JC_FIELD parent, const char *child_name,
						SHAPE_TYPE type);
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

/*
** ============================== Parse OFF files ==============================
*/
SHAPE		*parse_triangle(const char *filename, int *cnt, DTO_CAM *cam,
						char **err);
SHAPE		*get_triangles(const char *filename, int *cnt, DTO_CAM *cam,
						char **err);
SHAPE		*build_triangles(float **points, int **faces, int triangle_cnt,
						DTO_CAM *cam);
SHAPE		*create_triangle(float **points, int **faces, DTO_CAM *cam,
						int position);

int			parse_params(int fd, int *vertices_faces, char **err);
float		**get_points(int points_cnt, int fd, char **err);
int			**get_faces(int faces_cnt, int fd, char **err);
FLT3		get_point(float **points, int position);
void		set_triangle_points(DTO_SHAPE *dto, float **points, int **faces,
						int i);

int			set_params_from_line(char *line, int *vertices_faces, char **err);
float		*get_points_from_line(char *line);
int			*get_faces_from_line(char *line);
void		clear_points(float **points, int points_cnt);
void		clear_faces(int **points, int points_cnt);

int			common_check_off(int fd, char **err);
int			check_format(int fd, char **err);
int			check_params(int fd, int *params, char **err);
int			check_vertices(int fd, int *params, char **err);
int			check_faces(int fd, int *params, char **err);

int			check_file_off(const char *filename, char **err);
int			check_element_count(char *line, int count, int max, char **err);
int			check_params_count(char **splits, int count, int max, char **err);
void		free_splits(char **splits, int count);
int			error_safe(char **err, const char *text);

#endif
