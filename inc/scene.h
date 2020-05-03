/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 02:17:10 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/04 01:11:50 by cschoen          ###   ########lyon.fr   */
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
# define LIGHT_LIST struct s_list_light
# define SHAPE_LIST struct s_list_shape
# define TRANSFORM struct s_transform
# define MATERIAL struct s_material
# define FLT3 cl_float3

int	g_uid;

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

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct	s_material
{
	t_color		color;
	float		specular;
}				t_material;

typedef struct	s_transform
{
	FLT3		position;
	FLT3		direction;
	FLT3		rotation;
}				t_transform;

typedef struct	s_light
{
	LIGHT_TYPE	type;
	TRANSFORM	transform;
	float		intensity;
	float		radius;
}				t_light;

typedef struct	s_list_light
{
	LIGHT_TYPE	type;
	int			uid;
	t_light		*light;
	_Bool		marker;
	LIGHT_LIST	*next;
}				t_list_light;

typedef struct	s_plane
{
	SHAPE_TYPE	type;
	TRANSFORM	transform;
	MATERIAL	material;
}				t_plane;

typedef struct	s_sphere
{
	SHAPE_TYPE	type;
	TRANSFORM	transform;
	MATERIAL	material;
	float		radius;
}				t_sphere;

typedef struct	s_cone
{
	SHAPE_TYPE	type;
	TRANSFORM	transform;
	MATERIAL	material;
	float		angle;
}				t_cone;

typedef struct	s_cylinder
{
	SHAPE_TYPE	type;
	TRANSFORM	transform;
	MATERIAL	material;
	float		radius;
}				t_cylinder;

typedef struct	s_list_shape
{
	SHAPE_TYPE	type;
	int			uid;
	void		*shape;
	_Bool		marker;
	SHAPE_LIST	*next;
}				t_list_shape;

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
	LIGHT_LIST	*lights;
	SHAPE_LIST	*shapes;
}				t_scene;

#endif
