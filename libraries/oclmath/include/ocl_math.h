/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_math.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/13 23:29:59 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OCL_MATH_H
# define OCL_MATH_H

# ifdef __APPLE__
#  include "OpenCL/opencl.h"
# else
#  include "CL/cl.h"
# endif

# include <math.h>

# define FLT3 cl_float3
# define FLT2 cl_float2
# define INT2 cl_int2

/*
** ============================== Math constants ===============================
*/
# define PI 3.14159265359f
# define RAD 0.01745329251994f

/*
** =============================== cl_int2 math ================================
*/
INT2		i2_sub(INT2 i1, INT2 i2);
/*
** =============================== cl_float math ===============================
*/
cl_float	deg_to_rad(cl_float angle_in_degrees);
cl_float	rad_to_deg(cl_float angle_in_rad);
/*
** ============================== cl_float2 math ===============================
*/
cl_float	v2_dot(FLT2 v1, FLT2 v2);
cl_float	v2_det(FLT2 v1, FLT2 v2);
cl_float	v2_length(FLT2 v);
cl_float	v2_angle(FLT2 v1, FLT2 v2);

FLT2		v2_scale(FLT2 v, cl_float scale);
FLT2		v2_norm(FLT2 v);
/*
** ============================== cl_float3 math ===============================
*/
cl_float	v3_dot(FLT3 v1, FLT3 v2);
cl_float	v3_length_sq(FLT3 v);
cl_float	v3_length(FLT3 v);

FLT3		v3_add(FLT3 v1, FLT3 v2);
FLT3		v3_sub(FLT3 v1, FLT3 v2);
FLT3		v3_scale(FLT3 v, cl_float scale);
FLT3		v3_norm(FLT3 v);
FLT3		v3_cross(FLT3 v1, FLT3 v2);
/*
** ============================= cl_float3 rotate ==============================
*/
cl_float	v3_angle_to_xz(FLT3 v);

FLT3		v3_rot_x(FLT3 v, cl_float angle);
FLT3		v3_rot_y(FLT3 v, cl_float angle);
FLT3		v3_rot_z(FLT3 v, cl_float angle);
FLT3		v3_rot_v(FLT3 v, FLT3 k, cl_float angle);

#endif
