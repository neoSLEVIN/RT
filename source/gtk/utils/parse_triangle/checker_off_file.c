/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

int		common_check_off(int fd, char **err)
{
	int		last_line_count;
	int		vertices_faces[3];
	char	*line;

	if (check_format(fd, err))
		return (1);
	if (check_params(fd, vertices_faces, err))
		return (1);
	if (check_vertices(fd, vertices_faces, err))
		return (1);
	if (check_faces(fd, vertices_faces, err))
		return (1);
	last_line_count = get_next_line(fd, &line);
	if (last_line_count != 0)
	{
		free(line);
		error_safe(err, "last element not empty\n");
		return (1);
	}
	return (0);
}

int		check_format(int fd, char **err)
{
	char	*c;
	int		gn;
	int		res;

	if ((gn = get_next_line(fd, &c)) == 0)
		return (error_safe(err, "gnl error1"));
	res = ft_strcmp(c, "OFF");
	if (res != 0)
		return (error_safe(err, "wrong format - expected OFF"));
	free(c);
	return (0);
}

int		check_params(int fd, int *params, char **err)
{
	char	*c;
	int		i;
	char	**splits;

	i = 0;
	get_next_line(fd, &c);
	splits = ft_strsplit(c, 32);
	if (check_params_count(splits, 3, 0, err))
	{
		free(c);
		return (1);
	}
	while (i < 3)
	{
		params[i] = ft_atoi(splits[i]);
		if (i != 2 && params[i] == 0)
		{
			free_splits(splits, i);
			return (error_safe(err, "params need be not zero"));
		}
		i++;
	}
	free_splits(splits, 3);
	free(c);
	return (0);
}

int		check_vertices(int fd, int *params, char **err)
{
	int		verticles;
	int		i;
	char	*line;

	verticles = params[0];
	i = 0;
	while (i < verticles)
	{
		get_next_line(fd, &line);
		if (check_element_count(line, 3, 0, err))
			return (1);
		free(line);
		i++;
	}
	return (0);
}

int		check_faces(int fd, int *params, char **err)
{
	int		faces;
	int		i;
	char	*line;

	faces = params[1];
	i = 0;
	while (i < faces)
	{
		get_next_line(fd, &line);
		if (check_element_count(line, 4, params[0], err))
		{
			free(line);
			return (1);
		}
		if (*line != '3' && line[1] != ' ')
		{
			free(line);
			error_safe(err, "wrong count of points in faces");
			return (1);
		}
		free(line);
		i++;
	}
	return (0);
}
