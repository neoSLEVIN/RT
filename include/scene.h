/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 02:17:10 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/06 20:41:18 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "ocl_math.h"

# define LIGHT_TYPE enum e_light_type
enum			e_light_type
{
	AMBIENT,
	POINT,
	DIRECTION,
	CNT_OF_TYPES_L
};

# define SHAPE_TYPE enum e_shape_type
enum			e_shape_type
{
	PLANE,
	SPHERE,
	CONE,
	CYLINDER,
	CNT_OF_TYPES
};

# define MATERIAL struct s_material
struct			s_material
{
	FLT3		color;
	int			specular;
	FLT3		emission;
	cl_float	reflective;
	cl_float	transparency;
};

# define TRANSFORM struct s_transform
struct			s_transform
{
	FLT3		position;
	FLT3		direction;
	FLT3		rotation;
};

# define DTO_LIGHT struct s_dto_light
struct			s_dto_light
{
	LIGHT_TYPE	type;
	cl_float	intensity;
	FLT3		position;
	FLT3		direction;
	int			uid;
	int			marker;
};

# define LIGHT struct s_light
struct			s_light
{
	DTO_LIGHT	dto;
	LIGHT		*next;
};

# define DTO_SHAPE struct s_dto_shape
struct			s_dto_shape
{
	SHAPE_TYPE	type;
	TRANSFORM	transform;
	MATERIAL	material;
	cl_float	param;
	int			uid;
	int			marker;
};

# define SHAPE struct s_shape
struct			s_shape
{
	DTO_SHAPE	dto;
	SHAPE		*next;
};

typedef struct	s_camera
{
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
