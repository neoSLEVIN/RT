/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 02:17:10 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/06 07:01:52 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# ifdef __APPLE__
#  include "OpenCL/opencl.h"
# else
#  include "CL/cl.h"
# endif

# define LIGHT_TYPE enum e_light_type
# define SHAPE_TYPE enum e_shape_type
# define DTO_LIGHT struct s_dto_light
# define DTO_SHAPE struct s_dto_shape
# define LIGHT struct s_light
# define SHAPE struct s_shape
# define TRANSFORM struct s_transform
# define MATERIAL struct s_material
# define FLT3 cl_float3

typedef enum	e_light_type
{
	AMBIENT,
	POINT,
	DIRECTION,
	CNT_OF_TYPES_L
}				t_light_type;

typedef enum	e_shape_type
{
	PLANE,
	SPHERE,
	CONE,
	CYLINDER,
	CNT_OF_TYPES
}				t_shape_type;

typedef struct	s_material
{
	FLT3		color;
	int			specular;
	FLT3		emission;
	cl_float	reflective;
	cl_float	transparency;
}				t_material;

typedef struct	s_transform
{
	FLT3		position;
	FLT3		direction;
	FLT3		rotation;
}				t_transform;

struct			s_dto_light
{
	LIGHT_TYPE	type;
	cl_float	intensity;
	FLT3		position;
	FLT3		direction;
	int			uid;
	int			marker;
};

struct			s_light
{
	DTO_LIGHT	dto;
	LIGHT		*next;
};

struct			s_dto_shape
{
	SHAPE_TYPE	type;
	TRANSFORM	transform;
	MATERIAL	material;
	cl_float	param;
	int			uid;
	int			marker;
};

struct			s_shape
{
	DTO_SHAPE	dto;
	SHAPE		*next;
};

typedef struct	s_camera
{
	cl_int		screen_w;
	cl_int		screen_h;
	cl_float	viewport_h;
	cl_float	viewport_w;
	FLT3		origin;
	FLT3		target;
	FLT3		forward;
	FLT3		up;
	FLT3		right;
	FLT3		upguide;
	TRANSFORM	transform;
}				t_cam;

typedef struct	s_scene
{
	t_cam		cam;
	LIGHT		*lights;
	SHAPE		*shapes;
	int			l_cnt;
	int			s_cnt;
	LIGHT		*l_marker;
	SHAPE		*s_marker;
}				t_scene;

#endif
