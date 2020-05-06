/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_math.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 20:02:41 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/07 00:24:47 by cschoen          ###   ########lyon.fr   */
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
# define PI 3.14159265359f
# define RAD 0.01745329251994f

cl_float	degrees_to_rad(cl_float angle_in_degrees);
cl_float	v3_dot(FLT3 v1, FLT3 v2);
cl_float	v3_length_sq(FLT3 v);
cl_float	v3_length(FLT3 v);

FLT3		v3_add(FLT3 v1, FLT3 v2);
FLT3		v3_sub(FLT3 v1, FLT3 v2);
FLT3		v3_scale(FLT3 v, cl_float scale);
FLT3		v3_norm(FLT3 v);
FLT3		v3_cross(FLT3 v1, FLT3 v2);

FLT3		v3_rot_x(FLT3 v, cl_float angle);
FLT3		v3_rot_y(FLT3 v, cl_float angle);
FLT3		v3_rot_z(FLT3 v, cl_float angle);

#endif
