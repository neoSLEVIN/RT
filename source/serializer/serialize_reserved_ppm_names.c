/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize_reserved_ppm_names.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:32:14 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:32:14 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serializer.h"

static char	*get_reserved_normal_map_name(int index)
{
	char	*name;

	name = NULL;
	if (index == -1)
		name = ft_strdup("NO NORMALS");
	else
		ft_error("Unknown name (get_reserved_normal_map_name)");
	if (!name)
		ft_error("Can't allocate memory");
	return (name);
}

static char	*get_reserved_texture_name(int index)
{
	char	*name;

	name = NULL;
	if (index == -1)
		name = ft_strdup("NO TEXTURES");
	else if (index == -2)
		name = ft_strdup("Wood");
	else if (index == -3)
		name = ft_strdup("Noise");
	else if (index == -4)
		name = ft_strdup("Checker");
	else if (index == -5)
		name = ft_strdup("Lines");
	else
		ft_error("Unknown name (get_reserved_texture_name)");
	if (!name)
		ft_error("Can't allocate memory");
	return (name);
}

char		*get_ppm_name_by_index(PPM_IMG *ppm, int index, _Bool is_normal_map)
{
	int		i;
	char	*name;

	if (index < 0)
	{
		if (is_normal_map)
			return (get_reserved_normal_map_name(index));
		return (get_reserved_texture_name(index));
	}
	i = 0;
	while (ppm && i++ != index)
		ppm = ppm->next;
	if (!ppm)
		return (NULL);
	if (!(name = ft_strdup(ppm->name)))
		ft_error("Can't allocate memory");
	return (name);
}
