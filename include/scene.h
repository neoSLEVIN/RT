/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 02:17:10 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/06 03:09:51 by cschoen          ###   ########lyon.fr   */
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
	float		specular;
	float		reflective;
	float		transparency;
}				t_material;

typedef struct	s_transform
{
	FLT3		position;
	FLT3		direction;
	FLT3		rotation;
}				t_transform;

struct			s_light
{
	int			uid;
	_Bool		marker;
	LIGHT_TYPE	type;
	float		intensity;
	FLT3		position;
	FLT3		direction;
	float		radius;
	LIGHT		*next;
};

struct			s_shape
{
	int			uid;
	_Bool		marker;
	SHAPE_TYPE	type;
	TRANSFORM	transform;
	MATERIAL	material;
	float		param;
	SHAPE		*next;
};

typedef struct	s_camera
{
	TRANSFORM	transform;
	float		h;
	float		w;
	FLT3		origin;
	FLT3		target;
	FLT3		forward;
	FLT3		up;
	FLT3		right;
	FLT3		upguide;
}				t_cam;

typedef struct	s_scene
{
	t_cam		cam;
	LIGHT		*lights;
	SHAPE		*shapes;
	size_t		l_cnt;
	size_t		s_cnt;
	LIGHT		*l_marker;
	SHAPE		*s_marker;
}				t_scene;

#endif
