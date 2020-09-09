/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_image_import.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:30:26 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:30:27 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

static char		*get_header_info(char separator, int *start, int *end,
								char *buff)
{
	char	*str;

	*start = *end;
	while (*end < 40 && buff[*end] && buff[*end] != separator)
		(*end)++;
	if (*end == 40)
		return (NULL);
	if (!(str = ft_strsub(buff, *start, *end - *start)))
		ft_error("Can't allocate memory");
	(*end)++;
	return (str);
}

static _Bool	free_ppm_info(char **p6, char **width, char **height,
							char **max_color)
{
	if (*p6)
		ft_strdel(p6);
	if (*width)
		ft_strdel(width);
	if (*height)
		ft_strdel(height);
	if (*max_color)
		ft_strdel(max_color);
	return (FALSE);
}

static _Bool	setup_params(char *buff, DTO_PPM_IMG **dto, int *i, int *j)
{
	char	*p6;
	char	*width;
	char	*height;
	char	*max_color;

	p6 = NULL;
	width = NULL;
	height = NULL;
	max_color = NULL;
	if (!(p6 = get_header_info('\n', i, j, buff)))
		return (free_ppm_info(&p6, &width, &height, &max_color));
	if (!(width = get_header_info(' ', i, j, buff)))
		return (free_ppm_info(&p6, &width, &height, &max_color));
	if (!(height = get_header_info('\n', i, j, buff)))
		return (free_ppm_info(&p6, &width, &height, &max_color));
	if (!(max_color = get_header_info('\n', i, j, buff)))
		return (free_ppm_info(&p6, &width, &height, &max_color));
	(*dto)->width = ft_atoi(width);
	(*dto)->height = ft_atoi(height);
	(*dto)->max_color = ft_atoi(max_color);
	(*dto)->start_image = *j;
	free_ppm_info(&p6, &width, &height, &max_color);
	return (TRUE);
}

static _Bool	get_ppm_info(char *buff, DTO_PPM_IMG **dto, char **err)
{
	INT2	index;

	index = (INT2){0, 0};
	if (!setup_params(buff, dto, &index.x, &index.y))
		return (ppm_error_safe(err, "Invalid ppm", dto));
	if (!(buff[0] == 'P' && buff[1] == '6' && buff[2] == '\n'))
		return (ppm_error_safe(err, "First line must be \"P6\"", dto));
	if ((*dto)->width < MIN_DIMENSION || (*dto)->height < MIN_DIMENSION ||
			(*dto)->width > MAX_DIMENSION || (*dto)->height > MAX_DIMENSION)
		return (ppm_error_safe(err, "Second line: bad ppm resolution", dto));
	if ((*dto)->max_color != 255)
		return (ppm_error_safe(err, "Third line must be \"255\"", dto));
	return (TRUE);
}

_Bool			read_ppm_safe(const char *filename, DTO_PPM_IMG **dto,
							char **err)
{
	int		fd;
	char	buff[40];
	int		cnt;

	if (!(*dto = (DTO_PPM_IMG *)malloc(sizeof(DTO_PPM_IMG))))
		ft_error("Can't allocate memory");
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (ppm_error_safe(err, "Can't open the file", dto));
	cnt = read(fd, buff, 40);
	close(fd);
	if (cnt < 0)
		return (ppm_error_safe(err, "Bad read", dto));
	if (!get_ppm_info(buff, dto, err))
		return (FALSE);
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (ppm_error_safe(err, "Can't open the file", dto));
	read(fd, buff, (*dto)->start_image);
	read(fd, (*dto)->data, (*dto)->width * (*dto)->height * 3);
	close(fd);
	return (TRUE);
}
