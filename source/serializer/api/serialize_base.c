/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:31:26 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:31:26 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serializer.h"

static int	open_fd(const char *filename)
{
	FILE	*file;
	int		fd;

	if (!filename)
		ft_error("NPE: Name of the file");
	if (!(file = fopen(filename, "w+")))
		ft_error("Can't open the file");
	fclose(file);
	if ((fd = open(filename, O_WRONLY) < 0))
		ft_error("Can't open the file");
	close(fd);
	if ((fd = open(filename, O_WRONLY) < 0))
		ft_error("Can't open the file");
	return (fd);
}

void		s_open_serializer(t_serializer *s, const char *filename)
{
	s->indents = 0;
	s->fd = open_fd(filename);
}

void		s_close_serializer(t_serializer *s)
{
	close(s->fd);
}
