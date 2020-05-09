/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_get_object_name.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"

void	jcp_get_object_name(const char *json, size_t *i, JCP_OBJ *obj)
{
	jcp_skip_whitespaces(json, i);
	if (json[(*i)++] != '"')
		ft_error("Bad syntax of JSON");
	obj->name.start = &json[*i];
	while (json[*i] > 31 && json[*i] < 127 &&
			json[*i] != '"' && json[*i] != '\\' && ++(*i))
		++obj->name.length;
	if (json[(*i)++] != '"')
		ft_error("Bad syntax of JSON");
	if (obj->name.length == 0)
		obj->name.start = &obj->name.empty;
	jcp_skip_whitespaces(json, i);
}
