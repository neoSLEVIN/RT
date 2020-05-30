//
//  image_import.c
//  gtk_RT
//
//  Created by Dmitry Skorokohodov on 18/05/2020.
//  Copyright © 2020 Dmitry Skorokohodov. All rights reserved.
//

#include "gtk_module.h"

char	*get_header_info(char separator, int *start, int *end, char *buff)
{
	char	*str;

	*start = *end;
	while (buff[*end] != separator)
		(*end)++;
	str = ft_strsub(buff, *start, *end - *start);
	(*end)++;
	return (str);
}

void	setup_params(char *buff, DTO_PPM_IMG *dto, int *i, int *j)
{
	char	*width;
	char	*height;
	char	*max_color;

	get_header_info('\n', i, j, buff);
	width = get_header_info(' ', i, j, buff);
	height = get_header_info('\n', i, j, buff);
	max_color = get_header_info('\n', i, j, buff);
	dto->width = ft_atoi(width);
	dto->height = ft_atoi(height);
	dto->max_color = ft_atoi(max_color);
	dto->start_image = *j;
}

int		get_ppm_info(char *buff, DTO_PPM_IMG *dto)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	setup_params(buff, dto, &i, &j);
	//validate
	_Bool formatCheck = (buff[0] == 'P' && buff[1] == '6');
	_Bool demensionCheck1 = (dto->width > 0 && dto->height > 0);
	_Bool demensionCheck2 = (dto->width <= MAX_DIMENSION && dto->height <= MAX_DIMENSION);
	_Bool colorCheck = dto->max_color == 255;
	if (formatCheck && colorCheck && demensionCheck1 && demensionCheck2)
		return (0);
	return (1);
}

void	create_texture(const char *filename, DTO_PPM_IMG *dto)
{
	int	fd;

	size_t	size = dto->height * dto->width * 3;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error("Can't open the file (create_texture)");
	read(fd, NULL, dto->start_image);
	read(fd, dto->data, size);
}

DTO_PPM_IMG	*read_ppm(const char *filename)
{
	int			fd;
	char		buff[40];
	int			cnt;
	DTO_PPM_IMG	*dto;
	
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error("Can't open the file (read_ppm)");
	cnt = read(fd, buff, 40);
	close(fd);
	if (cnt < 0)
		ft_error("Bad read (read_ppm)");
	if (!(dto = (DTO_PPM_IMG *)malloc(sizeof(DTO_PPM_IMG))))
		ft_error("Bad malloc (DTO_PPM_IMG)");
	//TODO лучше не закрыть прогу а просто выводить сообщение о неудачном импорте
	if (get_ppm_info(buff, dto))
		ft_error("Validate fail (DTO_PPM_IMG)");
	create_texture(filename, dto);
	return dto;
}

void	read_ppm_to_texture(const char *filename, DTO_PPM_IMG *dto)
{
	int		fd;
	char	buff[40];
	int		cnt;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error("Can't open the file (read_ppm_to_texture)");
	cnt = read(fd, buff, 40);
	close(fd);
	if (cnt < 0)
		ft_error("Bad read (read_ppm)");
	//TODO лучше не закрыть прогу а просто выводить сообщение о неудачном импорте
	if (get_ppm_info(buff, dto))
		ft_error("Validate fail (DTO_PPM_IMG)");
	create_texture(filename, dto);
}
