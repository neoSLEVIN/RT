/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_get_value_of_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 02:34:03 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/03 02:34:03 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"

void	jcp_get_value_of_str(const char *json, size_t *i, t_jcp_object *obj)
{
	jcp_skip_whitespaces(json, i);
	if (json[(*i)++] != '"')
		ft_error("Bad syntax of JSON");
	obj->type |= JC_STR;
	obj->value.start = &json[*i];
	while (json[*i] > 31 && json[*i] < 127 &&
			json[*i] != '"' && json[*i] != '\\' && ++(*i))
		++obj->value.length;
	if (json[(*i)++] != '"')
		ft_error("Bad syntax of JSON");
	if (obj->value.length == 0)
		obj->value.start = &obj->value.empty;
	if (ft_isdigit(*obj->value.start) || *obj->value.start == '-')
		obj->type |= jcp_check_for_number(obj->value.start);
	jcp_skip_whitespaces(json, i);
}
