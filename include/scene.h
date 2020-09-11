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

# define MIN_WIDTH 100
# define MIN_HEIGHT 100

# ifndef PROJ_DIR
#  define PROJ_DIR ""
# endif

# ifdef __APPLE__
#  define SCENE_PATH PROJ_DIR"scene/"
#  define NORMAL_MAP_PATH PROJ_DIR"extras/normalmaps/"
#  define TEXTURE_PATH PROJ_DIR"extras/textures/"
#  define IMAGES_PATH PROJ_DIR"extras/images/"
#  define OFF_PATH PROJ_DIR"extras/off/"

# else
#  define SCENE_PATH PROJ_DIR"scene\\"
#  define NORMAL_MAP_PATH PROJ_DIR"extras\\normalmaps\\"
#  define TEXTURE_PATH PROJ_DIR"extras\\textures\\"
#  define IMAGES_PATH PROJ_DIR"extras\\images\\"
#  define OFF_PATH PROJ_DIR"extras\\off\\"
# endif

/*
** =============================================================================
** ============================= IMAGE resolution ==============================
** =================== You can add your favorite resolution: ===================
** # elif GTK_IMAGE_SIZE == (X)
** #  define COLS (WIDTH)
** #  define ROWS (HEIGHT)
** !!! Don't do it less than MIN_WIDTH and MIN_HEIGHT !!!
** =============================================================================
*/
# define GTK_IMAGE_SIZE 2
# if GTK_IMAGE_SIZE == 1
#  define COLS 1280
#  define ROWS 1024
# elif GTK_IMAGE_SIZE == 2
#  define COLS 1440
#  define ROWS 960
# elif GTK_IMAGE_SIZE == 3
#  define COLS 1024
#  define ROWS 768
# elif GTK_IMAGE_SIZE == 4
#  define COLS 800
#  define ROWS 600
# elif GTK_IMAGE_SIZE == 5
#  define COLS 640
#  define ROWS 480
# else
#  define COLS 320
#  define ROWS 200
# endif

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
};

/*
** === Light Node (Contains DTO, references to next/prev nodes and widgets) ====
*/
# define LIGHT struct s_light

struct			s_light
{
	DTO_LIGHT	*dto;
	char		*name;
	void		*tree_iter;
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
	CAPPEDCONE,
	CYLINDER,
	CAPSULE,
	CAPPEDCYLINDER,
	CIRCLE,
	CAPPEDPLANE,
	BOX,
	TRIANGLE,
	OFF
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
	cl_float	angle;
	FLT3		dots[3];
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
	cl_float	refraction;
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
	FLT3		params;
	_Bool		marker;
};

/*
** ==== Shape Node (Contains DTO, references to next/prev nodes and widget) ====
*/
# define SHAPE struct s_shape

struct			s_shape
{
	DTO_SHAPE	*dto;
	char		*name;
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
	INT2		max_screen;
	INT2		diff_screen;
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
	DTO_CAM		*dto;
	cl_float	fov;
	cl_float	fps;
	INT2		display;
	FLT3		position;
	FLT3		direction;
	cl_float	rotation;
};

/*
** =============================================================================
** ================================== PPM_IMG ==================================
** =============================================================================
*/
# define MAX_DIMENSION 1440
# define MIN_DIMENSION 100
# define MAX_PPM_IMG_SIZE 1440 * 1440 * 3

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
** =============================== OFF file Data ===============================
*/
typedef struct	s_off
{
	char		*filename;
	FLT3		*points;
	cl_int3		*faces;
	FLT3		*colors;
	int			p_cnt;
	int			f_cnt;
	char		*err;
	_Bool		open_fd;
	int			fd;
	char		*line;
	t_list		*list;
}				t_off;

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
	t_off		off;
	PPM_IMG		*textures;
	PPM_IMG		*normal_maps;
	int			l_cnt;
	int			s_cnt;
	int			t_cnt;
	int			n_cnt;
	FILTER		filter;
	FLT3		filter_params;
	int			anti_aliasing;
	cl_float	step;
	cl_float	angle;
	int			mirror;
	char		*filename;
};

#endif
