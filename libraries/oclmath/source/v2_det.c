/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v2_det.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 01:48:59 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/11 01:49:47 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl_math.h"

cl_float	v2_det(FLT2 v1, FLT2 v2)
{
	return (v1.x * v2.y - v1.y * v2.x);
}
