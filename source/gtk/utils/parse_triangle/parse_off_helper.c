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

int		set_params_from_line(char *line, int *vertices_faces, char **err)
{
	char	**splits;
	int		i;

	i = 0;
	if ((splits = ft_strsplit(line, 32)) == NULL)
		return (error_safe(err, "set_params_from_line NULL"));
	while (i < 2)
	{
		vertices_faces[i] = ft_atoi(splits[i]);
		i++;
	}
	return (0);
}

float	*get_points_from_line(char *line)
{
	char	**splits;
	float	*res;
	int		i;

	i = 0;
	if ((splits = ft_strsplit(line, 32)) == NULL)
		ft_error("get points splits empty");
	if ((res = (float*)malloc(sizeof(float) * 3)) == NULL)
		ft_error("Can't allocate memory");
	while (i < 3)
	{
		res[i] = atof(splits[i]);
		i++;
	}
	return (res);
}

int		*get_faces_from_line(char *line)
{
	char	**splits;
	int		*res;
	int		i;

	i = 0;
	splits = ft_strsplit(line, 32);
	if ((res = (int*)malloc(sizeof(int) * 4)) == NULL)
		ft_error("Can't allocate memory");
	while (i < 4)
	{
		res[i] = ft_atoi(splits[i]);
		i++;
	}
	return (res);
}

void	clear_points(float **points, int points_cnt)
{
	int i;

	i = 0;
	while (i < points_cnt)
	{
		free(points[i]);
		i++;
	}
	free(points);
}

void	clear_faces(int **points, int points_cnt)
{
	int i;

	i = 0;
	while (i < points_cnt)
	{
		free(points[i]);
		i++;
	}
	free(points);
}
