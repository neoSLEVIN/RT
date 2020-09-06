/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize_open.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:31:43 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:31:43 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serializer.h"

void	s_open_obj_no_indent(t_serializer *s)
{
	s_str(s, "{");
	s_indent_inc(s);
}

void	s_open_arr_no_indent(t_serializer *s)
{
	s_str(s, "[");
	s_indent_inc(s);
}

void	s_open_obj(t_serializer *s)
{
	s_indent(s);
	s_str(s, "{");
	s_indent_inc(s);
}

void	s_open_arr(t_serializer *s)
{
	s_indent(s);
	s_str(s, "[");
	s_indent_inc(s);
}
