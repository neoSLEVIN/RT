/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		no_leak(void **str1, char *str2, int res)
{
	char	*buf;

	str2[res] = '\0';
	buf = ft_strjoin(*str1, str2);
	ft_memdel(&(*str1));
	if (buf != NULL)
	{
		*str1 = ft_strdup(buf);
		ft_strdel(&buf);
	}
}

static t_list	*nodenew(t_list **node, const int fd)
{
	t_list	*start;
	t_list	*cur;

	cur = NULL;
	start = *node;
	while (*node != NULL && (*node)->content_size != (size_t)fd)
		*node = (*node)->next;
	if (*node == NULL)
	{
		*node = start;
		if ((start = ft_lstnew("", 1)) != NULL)
			start->content_size = fd;
		ft_lstadd(node, start);
	}
	cur = *node;
	*node = start;
	return (cur);
}

static int		nodedel(t_list **lst, char **line, const int fd, int res)
{
	t_list	*now;
	t_list	*prev;

	if (res < 0)
		res = -1;
	if (line != NULL && *lst != NULL && lst != NULL)
	{
		now = *lst;
		prev = *lst;
		while (now->content_size != (size_t)fd)
		{
			prev = now;
			now = now->next;
		}
		if (prev != now)
			prev->next = now->next;
		if (now->content != NULL)
			ft_memdel(&(now->content));
		if (prev == now)
			*lst = now->next;
		free(now);
		now = NULL;
	}
	return (res);
}

static int		put_in_line(char **line, t_list **cur)
{
	int		c;
	int		index;
	char	*buffer;

	buffer = NULL;
	c = (ft_strchr((*cur)->content, '\n') == NULL) ? '\0' : '\n';
	index = &(*ft_strchr((*cur)->content, c)) - &(*(char *)(*cur)->content);
	if (c == '\0')
		buffer = ft_strnew(0);
	else
		buffer = ft_strdup(ft_strchr((*cur)->content, c) + 1);
	if (buffer == NULL)
		return (-1);
	*line = ft_strsub((*cur)->content, 0, index);
	ft_memdel(&(*cur)->content);
	(*cur)->content = ft_strdup(buffer);
	ft_strdel(&buffer);
	return (((*cur)->content == NULL || *line == NULL) ? -1 : 1);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*lst;
	t_list			*cur;
	char			buff[BUFF_SIZE + 1];
	int				res;

	res = 1;
	buff[0] = '\0';
	cur = lst;
	if (fd < 0 || !line || BUFF_SIZE <= 0)
		return (fd < 0 ? -1 : nodedel(&lst, line, fd, -1));
	if (lst == NULL || lst->content_size != (size_t)fd)
		cur = nodenew(&lst, fd);
	while (res > 0 && cur->content != NULL && !(ft_strchr(buff, '\n')))
		if ((res = read(fd, buff, BUFF_SIZE)) > 0)
			no_leak(&(cur->content), buff, res);
	if (res >= 0 && cur->content != NULL && ft_strlen(cur->content))
		res = put_in_line(&(*line), &cur);
	if (res <= 0 || cur->content == NULL)
		return (nodedel(&lst, line, fd, cur->content == NULL ? -1 : res));
	return (1);
}
