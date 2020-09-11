/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize_type_name.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 05:56:55 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:32:34 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

char		*get_filter_type_name(FILTER filter)
{
	char	*name;

	name = NULL;
	if (filter == SEPIA)
		name = ft_strdup("SEPIA");
	else if (filter == NEGATIVE)
		name = ft_strdup("NEGATIVE");
	else if (filter == NOISE)
		name = ft_strdup("NOISE");
	else if (filter == SHADES_OF_GRAY)
		name = ft_strdup("SHADES OF GRAY");
	else if (filter == BLUR)
		name = ft_strdup("BLUR");
	else if (filter == EMBOSS)
		name = ft_strdup("EMBOSS");
	else if (filter == SHARPEN)
		name = ft_strdup("SHARPEN");
	else if (filter == NO_FILTER)
		name = ft_strdup("NO FILTERS");
	else
		ft_error("Unknown filter type (get_filter_type_name)");
	if (!name)
		ft_error("Can't allocate memory");
	return (name);
}

static char	*get_shape_type_name_norminette(SHAPE_TYPE type)
{
	char	*res;

	res = NULL;
	if (type == CAPPEDPLANE)
		res = ft_strdup("CAPPED PLANE");
	else if (type == BOX)
		res = ft_strdup("BOX");
	else if (type == TRIANGLE)
		res = ft_strdup("TRIANGLE");
	else if (type == OFF)
		res = ft_strdup("OFF");
	else
		ft_error("Unknown shape type (get_shape_type_name)");
	return (res);
}

char		*get_shape_type_name(SHAPE_TYPE type)
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
	else if (type == CAPPEDCONE)
		res = ft_strdup("CAPPED CONE");
	else if (type == CAPSULE)
		res = ft_strdup("CAPSULE");
	else if (type == CAPPEDCYLINDER)
		res = ft_strdup("CAPPED CYLINDER");
	else if (type == CIRCLE)
		res = ft_strdup("CIRCLE");
	else
		res = get_shape_type_name_norminette(type);
	if (res == NULL)
		ft_error("Can't allocate memory");
	return (res);
}

char		*get_light_type_name(LIGHT_TYPE type)
{
	char	*res;

	res = NULL;
	if (type == AMBIENT)
		res = ft_strdup("AMBIENT");
	else if (type == POINT)
		res = ft_strdup("POINT");
	else if (type == DIRECTION)
		res = ft_strdup("DIRECTION");
	else
		ft_error("Unknown light type (get_light_type_name)");
	if (res == NULL)
		ft_error("Can't allocate memory");
	return (res);
}
