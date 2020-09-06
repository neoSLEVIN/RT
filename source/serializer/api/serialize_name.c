/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:31:38 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:31:39 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serializer.h"

void	s_name_no_indent(t_serializer *s, const char *name)
{
	ft_printf("%[s\"%s\": ", s->fd, "", name, '"');
}

void	s_name(t_serializer *s, const char *name)
{
	s_indent(s);
	s_name_no_indent(s, name);
}

void	s_open_obj_with_name(t_serializer *s, const char *name)
{
	s_name(s, name);
	s_str(s, "{");
	s_indent_inc(s);
}

void	s_open_arr_with_name(t_serializer *s, const char *name)
{
	s_name(s, name);
	s_str(s, "[");
	s_indent_inc(s);
}
