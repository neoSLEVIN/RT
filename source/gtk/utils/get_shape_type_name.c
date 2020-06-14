/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shape_type_name.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 05:56:55 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/29 05:56:55 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

char	*get_shape_type_name(SHAPE_TYPE type)
{
	char	*res;

	if (type == PLANE)
		res = ft_strdup("PLANE");
	else if (type == SPHERE)
		res = ft_strdup("SPHERE");
	else if (type == CYLINDER)
		res = ft_strdup("CYLINDER");
	else if (type == CONE)
		res = ft_strdup("CONE");
	else if (type == CAPPEDCYLINDER)
		res = ft_strdup("CAPPED CYLINDER");
	else if (type == ELLIPSOID)
	    res = ft_strdup("ELLIPSOID");
    else if (type == ELLIPSE)
        res = ft_strdup("ELLIPSE");
	else
		ft_error("Unknown shape type (get_shape_type_name)");
	if (res == NULL)
		ft_error("Can't allocate memory");
	return (res);
}
