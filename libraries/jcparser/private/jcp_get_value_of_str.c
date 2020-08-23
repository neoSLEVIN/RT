/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_get_value_of_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/21 03:48:42 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"

static _Bool	jcp_full_check_for_valid_number(const char *value,
												const size_t length)
{
	size_t	i;

	i = -1;
	while (++i < length)
		if (!ft_isdigit(value[i]) && value[i] != '-' && value[i] != '.')
			return (FALSE);
	return (TRUE);
}

void			jcp_get_value_of_str(const char *json, size_t *i, JCP_OBJ *obj)
{
	jcp_skip_whitespaces(json, i);
	if (json[(*i)++] != '"')
		ft_error("Bad syntax of JSON");
	obj->type |= JC_STR;
	obj->value.start = &json[*i];
	while (((json[*i] > 31 && json[*i] < 127) || json[*i] < 0) &&
			json[*i] != '"' && ++(*i))
		++obj->value.length;
	if (json[(*i)++] != '"')
		ft_error("Bad syntax of JSON");
	if (obj->value.length == 0)
		obj->value.start = &obj->value.empty;
	else if ((ft_isdigit(*obj->value.start) || *obj->value.start == '-') &&
		jcp_full_check_for_valid_number(obj->value.start, obj->value.length))
		obj->type |= jcp_check_for_number(obj->value.start);
	jcp_skip_whitespaces(json, i);
}
