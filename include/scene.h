/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/17 03:32:42 by cschoen          ###   ########.fr       */
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
	PLANE,
	SPHERE,
	CONE,
	CYLINDER,
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
	int			specular;
	FLT3		emission;
	cl_float	reflective;
	cl_float	transparency;
};
/*
** ============================= Cut section info ==============================
*/
# define SECTION struct s_section
struct			s_section
{
	_Bool		on_x;
	_Bool		on_y;
	_Bool		on_z;
	TRANSFORM	x;
	TRANSFORM	y;
	TRANSFORM	z;
	TRANSFORM	xyz;
	FLT3		color;
};
/*
** ===== Shape Data Transfer Object (Set as an element of kernel argument) =====
*/
# define DTO_SHAPE struct s_dto_shape
struct			s_dto_shape
{
	SHAPE_TYPE	type;
	TRANSFORM	transform;
	MATERIAL	material;
	SECTION		section;
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
	void		*widgets;
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
	int			l_cnt;
	int			s_cnt;
	float		fps;
};

#endif
