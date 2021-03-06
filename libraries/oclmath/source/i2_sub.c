/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i2_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 00:30:27 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/16 00:30:27 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl_math.h"

INT2	i2_sub(INT2 i1, INT2 i2)
{
	i1.x -= i2.x;
	i1.y -= i2.y;
	return (i1);
}
