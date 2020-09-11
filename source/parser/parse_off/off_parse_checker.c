/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   off_parse_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amace-ty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 15:01:30 by amace-ty          #+#    #+#             */
/*   Updated: 2020/09/11 15:03:08 by amace-ty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

_Bool			off_check_params(t_off *off)
{
	char		*err_msg;

	err_msg = "Second line must be \"[points] [faces] [edges]\"";
	if ((get_next_line(off->fd, &off->line)) <= 0 || !off->line)
		return (off_deinit(off, TRUE, err_msg));
	if (!(off->list = ft_lstsplit(off->line, ' ')))
		return (off_deinit(off, TRUE, err_msg));
	(off->line) ? ft_strdel(&off->line) : 0;
	if (ft_lstlen(off->list) != 3)
		return (off_deinit(off, TRUE, err_msg));
	off->p_cnt = ft_atoi((char*)off->list->content);
	off->f_cnt = ft_atoi((char*)off->list->next->content);
	ft_lstdel(&off->list, ft_del);
	err_msg = "Second line must have positive counts of points and faces";
	if (off->p_cnt <= 0 || off->f_cnt <= 0)
		return (off_deinit(off, TRUE, err_msg));
	if (off->p_cnt > MAX_OFF_POINTS || off->f_cnt > MAX_OFF_FACES)
		return (off_deinit(off, TRUE,
				"Look max count for faces and points in "
				"MAX_OFF_POINTS and MAX_OFF_FACES"));
		return (TRUE);
}

_Bool			off_check_vertices(t_off *off)
{
	int			i;

	i = -1;
	while (++i < off->p_cnt)
	{
		if ((get_next_line(off->fd, &off->line)) <= 0 || !off->line)
			return (off_deinit(off, TRUE, "Bad point line read"));
		if (!(off->list = ft_lstsplit(off->line, ' ')))
			return (off_deinit(off, TRUE, "Bad point line split"));
		(off->line) ? ft_strdel(&off->line) : 0;
		if (ft_lstlen(off->list) != 3)
			return (off_deinit(off, TRUE, "Point must have 3 floats"));
		off->points[i].x = off_atof((char*)off->list->content);
		off->points[i].y = off_atof((char*)off->list->next->content);
		off->points[i].z = off_atof((char*)off->list->next->next->content);
		ft_lstdel(&off->list, ft_del);
	}
	return (TRUE);
}

static _Bool	off_validate_faces(t_off *off, int index, size_t len)
{
	if (off->faces[index].x < 0 || off->faces[index].x >= off->p_cnt ||
			off->faces[index].y < 0 || off->faces[index].y >= off->p_cnt ||
			off->faces[index].z < 0 || off->faces[index].z >= off->p_cnt)
		return (off_deinit(off, TRUE, "Bad point index in face"));
	if (len != 7)
		return (TRUE);
	if (off->colors[index].x < 0.0f || off->colors[index].x > 1.0f ||
			off->colors[index].y < 0.0f || off->colors[index].y > 1.0f ||
			off->colors[index].z < 0.0f || off->colors[index].z > 1.0f)
		return (off_deinit(off, TRUE, "Bad color value in face"));
	return (TRUE);
}

static _Bool	off_init_faces(t_off *off, int index, size_t len)
{
	int			point_cnt;
	t_list		*color;

	point_cnt = ft_atoi((char*)off->list->content);
	if (point_cnt != 3)
		return (off_deinit(off, TRUE,
				"The face must have 3 indexes of points"));
		off->faces[index].x = ft_atoi((char*)off->list->next->content);
	off->faces[index].y = ft_atoi((char*)off->list->next->next->content);
	off->faces[index].z = ft_atoi((char*)off->list->next->next->next->content);
	if (len == 7)
	{
		color = off->list->next->next->next->next;
		off->colors[index].x = off_atof((char*)color->content);
		off->colors[index].y = off_atof((char*)color->next->content);
		off->colors[index].z = off_atof((char*)color->next->next->content);
	}
	else
		off->colors[index] = (FLT3){-1.0f, -1.0f, -1.0f};
	return (off_validate_faces(off, index, len));
}

_Bool			off_check_faces(t_off *off)
{
	int			i;
	size_t		len;

	i = -1;
	while (++i < off->f_cnt)
	{
		if ((get_next_line(off->fd, &off->line)) <= 0 || !off->line)
			return (off_deinit(off, TRUE, "Bad face line read"));
		if (!(off->list = ft_lstsplit(off->line, ' ')))
			return (off_deinit(off, TRUE, "Bad face line split"));
		(off->line) ? ft_strdel(&off->line) : 0;
		if ((len = ft_lstlen(off->list)) != 4 && len != 7)
			return (off_deinit(off, TRUE,
		"The face must have count of point(3), "
		"their indexes(int) and color(optional)"));
			if (!off_init_faces(off, i, len))
			return (FALSE);
		ft_lstdel(&off->list, ft_del);
	}
	return (TRUE);
}
