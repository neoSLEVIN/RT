/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_text_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 21:17:50 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/02 12:02:49 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_text_file(const char *filename, size_t max_size)
{
	char	*file_text;
	int		fd;
	int		cnt;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error("Can't open the file (ft_get_text_file)");
	if (!(file_text = ft_strnew(max_size)))
		ft_error("Can't allocate memory (ft_get_text_file)");
	cnt = read(fd, file_text, max_size + 1);
	close(fd);
	if (cnt < 0)
		ft_error("Bad read (ft_get_text_file)");
	if (cnt > max_size)
		ft_error("Exceeded the maximum length of the file (ft_get_text_file)");
	return (file_text);
}
