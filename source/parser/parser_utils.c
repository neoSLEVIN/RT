/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:31:19 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:31:19 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char		*full_texture_path(const JC_FIELD parent,
							const JC_FIELD texture_field)
{
	char	*dir;
	char	*file;
	char	*path;

	dir = NULL;
	if (ft_strstr(jc_full_name(parent), "textures"))
		dir = TEXTURE_PATH;
	else if (ft_strstr(jc_full_name(parent), "normal maps"))
		dir = NORMAL_MAP_PATH;
	else
		ft_error("Unknown texture type (full_texture_path)");
	file = jc_get_string(texture_field, "path", FALSE);
	if (!(path = ft_strjoin(dir, file)))
		ft_error("Can't allocate memory");
	ft_strdel(&file);
	return (path);
}

char		*unnamed_obj(size_t index, char *prefix)
{
	char	*name;
	char	*str_index;

	if (!prefix)
		prefix = "Unnamed";
	if (!(str_index = ft_itoa((int)index)))
		ft_error("Can't allocate memory");
	if (!(name = ft_strnew(ft_strlen(prefix) + 1 + ft_strlen(str_index))))
		ft_error("Can't allocate memory");
	ft_strcpy(name, prefix);
	ft_strcat(name, "_");
	ft_strcat(name, str_index);
	ft_strdel(&str_index);
	return (name);
}

static void	reserved_parse_error(const JC_FIELD texture_field,
								_Bool is_normal_maps)
{
	parse_error(jc_full_name(texture_field), "name",
		is_normal_maps ?
			"A field can't have the same name as a reserved: [NO NORMALS]" :
			"A field can't have the same name as reserved names: "
			"[Lines, Checker, Noise, Wood, NO TEXTURES]");
}

void		check_reserved_names(const JC_FIELD texture_field, const char *name,
							_Bool is_normal_maps)
{
	if (is_normal_maps)
	{
		if (ft_strequ(name, "NO NORMALS"))
			reserved_parse_error(texture_field, is_normal_maps);
	}
	else
	{
		if (ft_strequ(name, "Lines") || ft_strequ(name, "Checker") ||
				ft_strequ(name, "Noise") || ft_strequ(name, "Wood") ||
				ft_strequ(name, "NO TEXTURES"))
			reserved_parse_error(texture_field, is_normal_maps);
	}
}

int			get_reserved_name_index(const char *name, _Bool is_normal_maps)
{
	if (is_normal_maps)
	{
		if (ft_strequ(name, "NO NORMALS"))
			return (-1);
	}
	else
	{
		if (ft_strequ(name, "NO TEXTURES"))
			return (-1);
		if (ft_strequ(name, "Wood"))
			return (-2);
		if (ft_strequ(name, "Noise"))
			return (-3);
		if (ft_strequ(name, "Checker"))
			return (-4);
		if (ft_strequ(name, "Lines"))
			return (-5);
	}
	return (0);
}
