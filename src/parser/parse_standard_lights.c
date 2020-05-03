/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_standard_lights.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 01:11:52 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/04 01:11:52 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_light	*parse_ambient(const JC_FIELD light_field, t_light *light)
{
	if (!light)
		return (NULL);
	light->type = AMBIENT;
	light->transform = parse_transform(light_field, "transform");
	return (light);
}

t_light	*parse_point(const JC_FIELD light_field, t_light *light)
{
	if (!light)
		return (NULL);
	light->type = POINT;
	light->transform = parse_transform(light_field, "transform");
	return (light);
}

t_light	*parse_direction(const JC_FIELD light_field, t_light *light)
{
	if (!light)
		return (NULL);
	light->type = DIRECTION;
	light->transform = parse_transform(light_field, "transform");
	return (light);
}
