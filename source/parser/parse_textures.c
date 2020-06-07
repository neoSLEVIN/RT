/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 22:42:56 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/24 14:40:04 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int			check_for_texture_name(PPM_IMG *texture, const char *name)
{
	int	index;

	index = 0;
	if (name == NULL)
		return (-2);
	while (texture)
	{
		if (ft_strequ(name, texture->name))
			return (index);
		++index;
		texture = texture->next;
	}
	return (-1);
}

TEXTURE		parse_texture_info_in_shape(const JC_FIELD parent,
				const char *child_name, char **texture_name, PPM_IMG *textures)
{
	JC_FIELD	texture_field;
	TEXTURE		texture;

	texture_field = jc_get_field(parent, child_name, (JC_OBJ | JC_NULL));
	if (jc_is_null(texture_field))
	{
		texture.id = -1;
		texture.direction = (FLT3){0.0f, 1.0f, 0.0f};
		texture.rotation = 0.0f;
		return (texture);
	}
	if (!(*texture_name = jc_get_string(texture_field, "name", TRUE)))
		texture.id = -1;
	//TODO check for our inside textures (checkmate, etc)
	else if ((texture.id =
				check_for_texture_name(textures, *texture_name)) == -1)
		parse_error(jc_full_name(texture_field), "name",
					"There is no field with this name");
	texture.direction = parse_cl_float3_or_default(texture_field, "direction",
		(FLT3){0.0f, 1.0f, 0.0f});
	texture.rotation = jc_get_float_or_default(texture_field, "rotation", 0.0f);
	return (texture);
}

static void	error_on_same_texture_name(const JC_FIELD parent, PPM_IMG *texture)
{
	int	index;
	int	res;

	index = 0;
	while (texture)
	{
		res = check_for_texture_name(texture->next, texture->name);
		if (res == -2)
			ft_error("NPE: (error_on_same_texture_name)");
		if (res != -1)
			parse_error(jc_full_name(jc_get_field_idx(parent, index + res + 1,
				JC_OBJ)), "name", "A ppm_img with this name exists");
		++index;
		texture = texture->next;
	}
}

PPM_IMG		*parse_texture_idx(const JC_FIELD parent, const size_t index)
{
	JC_FIELD	texture_field;
	PPM_IMG		*texture;
	size_t		length;

	texture_field = jc_get_field_idx(parent, index, JC_OBJ);
	texture = (PPM_IMG*)malloc(sizeof(PPM_IMG));
	if (!texture || !(texture->dto = (DTO_PPM_IMG*)malloc(sizeof(DTO_PPM_IMG))))
		ft_error("Can't allocate memory");
	texture->prev = NULL;
	texture->next = NULL;
	texture->dto = NULL;
	texture->name = jc_get_string(texture_field, "name", FALSE);
	length = ft_strlen(texture->name);
	if (length == 0 || length > 20)
		parse_error(jc_full_name(texture_field), "name",
			"The field length must be in the range (0; 20].");
	texture->path = jc_get_string(texture_field, "path", FALSE);
	return (texture);
}

PPM_IMG	*parse_textures(const JC_FIELD parent, const char *child_name)
{
	JC_FIELD	textures_field;
	PPM_IMG		*textures;
	PPM_IMG		*temp_texture;
	size_t		length;
	size_t		i;

	textures_field = jc_get_field(parent, child_name, (JC_ARR | JC_NULL));
	if (jc_is_null(textures_field))
		return (NULL);
	length = jc_get_array_length(textures_field);
	if (length == 0)
		return (NULL);
	textures = parse_texture_idx(textures_field, 0);
	temp_texture = textures;
	i = 0;
	while (++i < length)
	{
		temp_texture->next = parse_texture_idx(textures_field, i);
		temp_texture->next->prev = temp_texture;
		temp_texture = temp_texture->next;
	}
	error_on_same_texture_name(textures_field, textures);
	return (textures);
}
