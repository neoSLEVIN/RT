/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 02:17:10 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/05 19:33:44 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
#define SCENE_H

# ifdef __APPLE__
#  include "OpenCL/opencl.h"
# else
#  include "CL/cl.h"
# endif

typedef enum			e_light_type
{
	AMBIENT,
	POINT,
	DIRECTION,
	CNT_OF_TYPES_L
}						t_light_type;

typedef enum			e_shape_type
{
	PLANE,
	SPHERE,
	CONE,
	CYLINDER,
	CNT_OF_TYPES
}						t_shape_type;

typedef struct			s_color
{
	int					r;
	int					g;
	int					b;
}						t_color;

typedef struct			s_material
{
	t_color				color;
	float				specular;
}						t_material;

typedef struct			s_transform
{
	cl_float3			position;
	cl_float3			direction;
	cl_float3			rotation;
}						t_transform;

typedef struct			s_light
{
	t_light_type		type;
	t_transform			transform;
	float				intensity;
	float				radius;
}						t_light;

typedef struct			s_list_light
{
	t_light_type		type;
	t_light				*light;
	struct s_list_light	*next;
}						t_list_light;

typedef struct			s_plane
{
	t_shape_type		type;
	t_transform			transform;
	t_material			material;
}						t_plane;

typedef struct			s_sphere
{
	t_shape_type		type;
	t_transform			transform;
	t_material			material;
	float				radius;
}						t_sphere;

typedef struct			s_cone
{
	t_shape_type		type;
	t_transform			transform;
	t_material			material;
	float				angle;
}						t_cone;

typedef struct			s_cylinder
{
	t_shape_type		type;
	t_transform			transform;
	t_material			material;
	float				radius;
}						t_cylinder;

typedef struct			s_list_shape
{
	t_shape_type		type;
	int					uid;
	void				*shape;
	_Bool				marker;
	struct s_list_shape	*next;
}						t_list_shape;

typedef struct			s_camera
{
	t_transform			transform;
	// float				h;
	// float				w;
	// float3				origin;
	// float3				target;
	// float3				forward;
	// float3				up;
	// float3				right;
	// float3				upguide;
}						t_cam;

typedef struct			s_scene
{
	t_cam				cam;
	t_list_light		*lights;
	t_list_shape		*shapes;
}						t_scene;

#endif
