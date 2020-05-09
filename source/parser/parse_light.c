/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

LIGHT		*parse_light_idx(const JC_FIELD parent, const int index)
{
	JC_FIELD	light_field;
	LIGHT		*light;

	light_field = jc_get_field_idx(index, parent, JC_OBJ);
	if((light = (LIGHT*)malloc(sizeof(LIGHT))) == NULL)
		ft_error("Can't allocate memory");
	light->next = NULL;
	light->dto.marker = FALSE;
	light->dto.type = parse_light_type(light_field, "type");
	light->dto.intensity = jc_get_float(light_field, "intensity");
	// TODO validate intensity value
	light->dto.position = parse_cl_float3(light_field, "position");
	light->dto.direction = parse_cl_float3(light_field, "direction");
	// TODO parse another params
	return (light);
}

LIGHT		*parse_lights(const JC_FIELD parent, const char *child_name)
{
	JC_FIELD	lights_field;
	LIGHT		*lights;
	LIGHT		*temp_light;
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
