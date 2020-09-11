/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   off_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amace-ty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 15:01:08 by amace-ty          #+#    #+#             */
/*   Updated: 2020/09/11 15:01:10 by amace-ty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

_Bool		off_init(t_off *off, char *filename)
{
	off->filename = filename;
	off->points = NULL;
	off->faces = NULL;
	off->colors = NULL;
	off->p_cnt = 0;
	off->f_cnt = 0;
	off->err = NULL;
	off->line = NULL;
	off->list = NULL;
	off->open_fd = FALSE;
	if ((off->fd = open(filename, O_RDONLY)) < 0)
		return (off_deinit(off, TRUE, "Can't open the file"));
	off->open_fd = TRUE;
	return (TRUE);
}

_Bool		off_deinit(t_off *off, _Bool clean_all, const char *err_msg)
{
	size_t	err_len;

	(clean_all && off->points) ? ft_memdel((void**)&off->points) : 0;
	(clean_all && off->faces) ? ft_memdel((void**)&off->faces) : 0;
	(clean_all && off->colors) ? ft_memdel((void**)&off->colors) : 0;
	(off->list) ? ft_lstdel(&off->list, ft_del) : 0;
	(off->line) ? ft_strdel(&off->line) : 0;
	(off->open_fd) ? close(off->fd) : 0;
	off->open_fd = FALSE;
	err_len = 0;
	if (err_msg)
	{
		if (off->filename)
			err_len = ft_strlen(off->filename) + ft_strlen(": ");
		err_len += ft_strlen(err_msg) + ft_strlen("\n");
		(off->err) ? ft_strdel(&off->err) : 0;
		if (!(off->err = ft_strnew(err_len)))
			ft_error("Can't allocate memory");
		if (off->filename)
			ft_strcat(ft_strcat(off->err, off->filename), ": ");
		ft_strcat(ft_strcat(off->err, err_msg), "\n");
		return (FALSE);
	}
	return (TRUE);
}

cl_float	off_atof(char *num)
{
	char	*dot;
	double	dbl;
	char	test_str[4];

	ft_strcpy(test_str, "0.1");
	dot = ft_strchr(num, '.');
	if (dot != NULL && atof(test_str) != 0.1)
		*dot = ',';
	dbl = atof(num);
	return ((cl_float)dbl);
}
