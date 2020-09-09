/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_text_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	open_file_error(const char *filename)
{
	char	*text_error;
	char	*res;

	text_error = "Can't open the file (ft_get_text_file): ";
	res = ft_strnew(ft_strlen(text_error) + ft_strlen(filename));
	if (res == NULL)
		ft_error(text_error);
	ft_strcpy(res, text_error);
	ft_strcat(res, filename);
	ft_error(res);
}

char		*ft_get_text_file(const char *filename, size_t max_size)
{
	char	*file_text;
	int		fd;
	int		cnt;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		open_file_error(filename);
	if (!(file_text = ft_strnew(max_size)))
		ft_error("Can't allocate memory (ft_get_text_file)");
	cnt = read(fd, file_text, max_size + 1);
	close(fd);
	if (cnt < 0)
		ft_error("Bad read (ft_get_text_file)");
	if ((size_t)cnt > max_size)
		ft_error("Exceeded the maximum length of the file (ft_get_text_file)");
	return (file_text);
}
