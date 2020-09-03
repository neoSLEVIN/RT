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

void		check_for_ambient(LIGHT *light, const JC_FIELD *lights_field)
{
	int	ambient_cnt;

	ambient_cnt = 0;
	while (light)
	{
		if (light->dto->type == AMBIENT)
			++ambient_cnt;
		light = light->next;
	}
	if (ambient_cnt != 1)
		parse_error(jc_full_name(*lights_field), NULL,
			"The list must contain object with the type AMBIENT. "
			"AMBIENT must be only one in list.");
}

char		*parse_light_name(const JC_FIELD *light_field, const size_t index)
{
	char	*name;
	size_t	length;

	name = jc_get_string(*light_field, "name", TRUE);
	if (!name)
		name = unnamed_obj(index + 1, NULL);
	length = ft_strlen_rus(name);
	if (length == 0 || length > 20)
		parse_error(jc_full_name(*light_field), "name",
			"The field length must be in the range (0; 20].");
	return (name);
}

LIGHT		*parse_light_idx(const JC_FIELD parent, const size_t index)
{
	JC_FIELD	light_field;
	LIGHT		*light;

	light_field = jc_get_field_idx(parent, index, JC_OBJ);
	light = (LIGHT*)malloc(sizeof(LIGHT));
	if (!light || !(light->dto = (DTO_LIGHT*)malloc(sizeof(DTO_LIGHT))))
		ft_error("Can't allocate memory");
	light->prev = NULL;
	light->next = NULL;
	light->tree_iter = NULL;
	light->name = parse_light_name(&light_field, index);
	light->dto->type = parse_light_type(light_field, "type");
	light->dto->intensity = jc_get_float(light_field, "intensity");
	if (light->dto->intensity < 0.01f || light->dto->intensity > 1.0f)
		parse_error(jc_full_name(light_field), "intensity",
					"Value must be in range [0.01; 1.00].");
	light->dto->position = parse_cl_float3_or_default(light_field, "position",
										(FLT3){0.0f, 0.0f, 0.0f});
	light->dto->direction = parse_cl_float3_or_default(light_field, "direction",
										(FLT3){0.0f, -1.0f, 0.0f});
	if (v3_length(light->dto->direction) == 0.0f)
		parse_error(jc_full_name(light_field), "direction",
					"The vector must not be a zero vector.");
	return (light);
}

LIGHT		*parse_lights(const JC_FIELD parent, const char *child_name)
{
	JC_FIELD	lights_field;
	LIGHT		*lights;
	LIGHT		*temp_light;
	size_t		length;
	size_t		i;

	lights_field = jc_get_field(parent, child_name, JC_ARR);
	length = jc_get_array_length(lights_field);
	if (length == 0)
		parse_error(jc_full_name(parent), child_name,
			"The array must not be empty.");
	lights = parse_light_idx(lights_field, 0);
	temp_light = lights;
	i = 0;
	while (++i < length)
	{
		temp_light->next = parse_light_idx(lights_field, i);
		temp_light->next->prev = temp_light;
		temp_light = temp_light->next;
	}
	check_for_ambient(lights, &lights_field);
	return (lights);
}
