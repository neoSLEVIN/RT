//
//  image_import.c
//  gtk_RT
//
//  Created by Dmitry Skorokohodov on 18/05/2020.
//  Copyright © 2020 Dmitry Skorokohodov. All rights reserved.
//

#include "gtk_module.h"

char *get_header_info(char separator, int *start, int *end, char *buff) {
	char *str;
	
	*start = *end;
	while (buff[*end] != separator)
		(*end)++;
	str = ft_strsub(buff, *start, *end - *start);
	(*end)++;
	return  str;
}

void setup_params(char *buff, t_ppm_image *image, int *i, int *j) {
	char *width;
	char *height;
	char *max_color;
	
	get_header_info('\n', i, j, buff);
	width = get_header_info(' ', i, j, buff);
	height = get_header_info('\n', i, j, buff);
	max_color = get_header_info('\n', i, j, buff);
	image->width = ft_atoi(width);
	image->height = ft_atoi(height);
	image->max_color = ft_atoi(max_color);
	image->start_image = *j;
}

int get_ppm_info(char *buff, t_ppm_image *image) {
	int i;
	int j;
	
	i = 0;
	j = 0;
	setup_params(buff, image, &i, &j);
	//validate
	bool formatCheck = (buff[0] == 'P' && buff[1] == '6');
	bool demensionCheck = (image->width > 0 && image->height > 0);
	bool colorCheck = image->max_color == 255;
	if (formatCheck && demensionCheck && colorCheck)
		return 0;
	return 1;
}

void create_image(const char *filename, t_ppm_image *image) {
	int fd;
	
	size_t size = image->height * image->width * 3;
	image->data = malloc(size);
	if (image->data == NULL)
		ft_error("Malloc");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error("Can't open the file (readPPM)");
	read(fd, NULL, image->start_image);
	read(fd, image->data, size);
}

t_ppm_image *readPPM(const char *filename) {
	int			fd;
	char 		buff[40];
	int 		cnt;
	t_ppm_image *image;
	
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error("Can't open the file (readPPM)");
	cnt = read(fd, buff, 40);
	close(fd);
	if (cnt < 0)
		ft_error("Bad read (readPPM)");
	if (!(image = (t_ppm_image *)malloc(sizeof(t_ppm_image))))
		ft_error("Bad malloc (t_ppm_image)");
	if (get_ppm_info(buff, image))
		ft_error("Validate fail (t_ppm_image)");
	create_image(filename, image);
	return image;
}
