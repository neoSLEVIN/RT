/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/29 07:18:49 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "ocl_math.h"

/*
** =============================================================================
** =================================== LIGHT ===================================
** =============================================================================
*/

/*
** ================================ Light types ================================
*/
# define LIGHT_TYPE enum e_light_type
enum			e_light_type
{
	AMBIENT,
	POINT,
	DIRECTION,
	CNT_OF_TYPES_L
};
/*
** ===== Light Data Transfer Object (Set as an element of kernel argument) =====
*/
# define DTO_LIGHT struct s_dto_light
struct			s_dto_light
{
	LIGHT_TYPE	type;
	cl_float	intensity;
	FLT3		position;
	FLT3		direction;
	_Bool		marker;
};
/*
** === Light Node (Contains DTO, references to next/prev nodes and widgets) ====
*/
# define LIGHT struct s_light
struct			s_light
{
	DTO_LIGHT	*dto;
	char		*name;
	void		*widgets;
	LIGHT		*prev;
	LIGHT		*next;
};

/*
** =============================================================================
** =================================== SHAPE ===================================
** =============================================================================
*/

/*
** ================================ Shape types ================================
*/
# define SHAPE_TYPE enum e_shape_type
enum			e_shape_type
{
	NONE,
	PLANE,
	SPHERE,
	CONE,
	CYLINDER,
	CAPPEDCYLINDER,
	CNT_OF_TYPES
};
/*
** =============================== Location info ===============================
*/
# define TRANSFORM struct s_transform
struct			s_transform
{
	FLT3		position;
	FLT3		direction;
	FLT3		rotation;
};
/*
** ============================== Properties info ==============================
*/
# define MATERIAL struct s_material
struct			s_material
{
	FLT3		color;
	cl_float	specular;
	FLT3		emission;
	cl_float	reflective;
	cl_float	transparency;
};
/*
** =============================== Texture info ================================
*/
# define TEXTURE struct s_texture
struct			s_texture
{
	int			id;
	FLT3		direction;
	cl_float	rotation;
};
/*
** ============================= Cut section info ==============================
*/
# define SECTION struct s_section
struct			s_section
{
	_Bool		on;
	SHAPE_TYPE	type;
	FLT3		position;
	FLT3		direction;
	cl_float	param;
};
# define SECTION_CNT 6

/*
** ===== Shape Data Transfer Object (Set as an element of kernel argument) =====
*/
# define DTO_SHAPE struct s_dto_shape
struct			s_dto_shape
{
	SHAPE_TYPE	type;
	TRANSFORM	transform;
	MATERIAL	material;
	TEXTURE		texture;
	TEXTURE		normal_map;
	SECTION		sections[SECTION_CNT];
	cl_int		working_sections;
	_Bool		is_complex_section;
	cl_float	param;
	_Bool		marker;
};
/*
** === Shape Node (Contains DTO, references to next/prev nodes and widgets) ====
*/
# define SHAPE struct s_shape
struct			s_shape
{
	DTO_SHAPE	*dto;
	char		*name;
	void		*widgets;
	void		*tree_iter;
	char		*texture_name;
	char		*normal_map_name;
	SHAPE		*prev;
	SHAPE		*next;
};

/*
** =============================================================================
** =================================== CAMERA ==================================
** =============================================================================
*/

/*
** ========== Camera Data Transfer Object (Set as a kernel argument) ===========
*/
# define DTO_CAM struct s_dto_cam
struct			s_dto_cam
{
	int			screen_w;
	int			screen_h;
	cl_float	viewport_h;
	cl_float	viewport_w;
	FLT3		origin;
	FLT3		target;
	FLT3		forward;
	FLT3		up;
	FLT3		right;
	FLT3		upguide;
};
/*
** =================== Info about parsed camera data and DTO ===================
*/
# define CAMERA struct s_camera
struct			s_camera
{
//	DTO_CAM		*dto;
	FLT3		position;
	FLT3		direction;
	cl_float	rotation;
};

/*
** =============================================================================
** ================================== PPM_IMG ==================================
** =============================================================================
*/
# define MAX_DIMENSION 640
# define MIN_DIMENSION 100
# define MAX_PPM_IMG_SIZE 640 * 640 * 3
/*
** === PPM image Data Transfer Object (Set as an element of kernel argument) ===
*/
# define DTO_PPM_IMG struct s_dto_ppm_img
struct			s_dto_ppm_img
{
	char		data[MAX_PPM_IMG_SIZE];
	int			width;
	int			height;
	int			max_color;
	int			start_image;
};
/*
** == PPM image Node (Contains DTO, name, path, references to next/prev nodes) =
*/
# define PPM_IMG struct s_ppm_img
struct			s_ppm_img
{
	DTO_PPM_IMG	*dto;
	char		*name;
	char		*path;
	PPM_IMG		*prev;
	PPM_IMG		*next;
};

/*
** =============================================================================
** ================================== FILTERS ==================================
** =============================================================================
*/
# define FILTER enum e_filters
enum			e_filters
{
	NO_FILTER,
	SEPIA,
	NEGATIVE,
	NOISE,
	SHADES_OF_GRAY,
	BLUR,
	EMBOSS,
	SHARPEN
};

/*
** =============================================================================
** =========================== Main Entity for Scene ===========================
** ==== Contains information about camera, shapes, lights and app settings =====
** =============================================================================
*/
# define SCENE struct s_scene
struct			s_scene
{
	CAMERA		cam;
	LIGHT		*lights;
	SHAPE		*shapes;
	PPM_IMG		*textures;
	PPM_IMG		*normal_maps;
	int			l_cnt;
	int			s_cnt;
	int			t_cnt;
	int			n_cnt;
	float		fps;
	FILTER		filter;
};

#endif
