/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 00:49:31 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/05 07:37:29 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_light	*parse_light_fields_by_type(const JC_FIELD parent,
											LIGHT_TYPE type)
{
	t_light	*light;

	if(!(light = (t_light*)malloc(sizeof(t_light))))
		ft_error("Can't allocate memory");
	if (type == AMBIENT)
		return (parse_ambient(parent, light));
	else if (type == POINT)
		return (parse_point(parent, light));
	else if (type == DIRECTION)
		return (parse_direction(parent, light));
	else
		ft_error("Unknown action");
	return (NULL);
}

LIGHT_LIST		*parse_light_idx(const JC_FIELD parent, const int index)
{
	JC_FIELD	light_field;
	LIGHT_LIST	*light;

	light_field = jc_get_field_idx(index, parent, JC_OBJ);
	if(!(light = (LIGHT_LIST*)malloc(sizeof(LIGHT_LIST))))
		ft_error("Can't allocate memory");
	light->uid = g_uid++;
	light->marker = FALSE;
	light->next = NULL;
	light->type = parse_light_type(light_field, "type");
	light->light = parse_light_fields_by_type(light_field, light->type);
	return (light);
}

LIGHT_LIST		*parse_lights(const JC_FIELD parent, const char *child_name)
{
	JC_FIELD	lights_field;
	LIGHT_LIST	*lights;
	LIGHT_LIST	*temp_light;
	size_t		length;
	size_t		i;

	lights_field = jc_get_field(child_name, parent, JC_ARR);
	length = jc_get_array_length(lights_field);
	if (length == 0)
		parse_error(jc_full_name(parent), child_name,
			" The array must not be empty.");
	lights = parse_light_idx(lights_field, 0);
	temp_light = lights;
	i = 0;
	while (++i < length)
	{
		temp_light->next = parse_light_idx(lights_field, i);
		temp_light = temp_light->next;
	}
	return (lights);
}
