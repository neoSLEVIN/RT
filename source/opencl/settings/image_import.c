/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_import.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:30:19 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:30:20 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

static void	ppm_error(const char *error, const char *filename)
{
	ft_printf("Error: PPM: %s: %s\n", error, filename);
	exit(1);
}

static char	*get_header_info(char separator, int *start, int *end, char *buff)
{
	char	*str;

	*start = *end;
	while (*end < 40 && buff[*end] && buff[*end] != separator)
		(*end)++;
	if (*end == 40)
		ft_error("Invalid ppm");
	if (!(str = ft_strsub(buff, *start, *end - *start)))
		ft_error("Can't allocate memory");
	(*end)++;
	return (str);
}

static void	setup_params(char *buff, DTO_PPM_IMG *dto, int *i, int *j)
{
	char	*p6;
	char	*width;
	char	*height;
	char	*max_color;

	p6 = get_header_info('\n', i, j, buff);
	width = get_header_info(' ', i, j, buff);
	height = get_header_info('\n', i, j, buff);
	max_color = get_header_info('\n', i, j, buff);
	dto->width = ft_atoi(width);
	dto->height = ft_atoi(height);
	dto->max_color = ft_atoi(max_color);
	dto->start_image = *j;
	ft_strdel(&p6);
	ft_strdel(&width);
	ft_strdel(&height);
	ft_strdel(&max_color);
}

static void	get_ppm_info(char *buff, DTO_PPM_IMG *dto, const char *filename)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	setup_params(buff, dto, &i, &j);
	if (!(buff[0] == 'P' && buff[1] == '6' && buff[2] == '\n'))
		ppm_error("First string must be \"P6\"", filename);
	if (!(dto->width >= MIN_DIMENSION && dto->height >= MIN_DIMENSION &&
			dto->width <= MAX_DIMENSION && dto->height <= MAX_DIMENSION))
	{
		ft_printf("Error: PPM: second line: %s [%d; %d]\n",
			"Resolution of the side must be in range",
			MIN_DIMENSION, MAX_DIMENSION);
		exit(1);
	}
	if (dto->max_color != 255)
		ppm_error("Third string must be \"255\"", filename);
}

DTO_PPM_IMG	*read_ppm(const char *filename)
{
	int			fd;
	char		buff[40];
	int			cnt;
	DTO_PPM_IMG	*dto;

	if (!(dto = (DTO_PPM_IMG *)malloc(sizeof(DTO_PPM_IMG))))
		ft_error("Can't allocate memory");
	if ((fd = open(filename, O_RDONLY)) < 0)
		ppm_error("Can't open the file", filename);
	cnt = read(fd, buff, 40);
	close(fd);
	if (cnt < 0)
		ppm_error("Bad read", filename);
	get_ppm_info(buff, dto, filename);
	if ((fd = open(filename, O_RDONLY)) < 0)
		ppm_error("Can't open the file", filename);
	read(fd, buff, dto->start_image);
	read(fd, dto->data, dto->width * dto->height * 3);
	close(fd);
	return (dto);
}
