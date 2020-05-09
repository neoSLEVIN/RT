/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_get_value_of_obj_or_arr.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"

void	jcp_get_value_of_obj_or_arr(const char *json, size_t *i, JCP_OBJ *obj)
{
	jcp_skip_whitespaces(json, i);
	if (json[*i] != '{' && json[*i] != '[')
		ft_error("Bad syntax of JSON");
	obj->value.start = &json[*i];
	obj->type |= (json[(*i)++] == '{') ? JC_OBJ : JC_ARR;
	jcp_skip_whitespaces(json, i);
	if (((obj->type & JC_OBJ) && json[*i] == '}') ||
		((obj->type & JC_ARR) && json[*i] == ']'))
	{
		++(*i);
		jcp_skip_whitespaces(json, i);
	}
	else
	{
		obj->child = (obj->type & JC_OBJ) ?
			jcp_get_object(json, i) :
			jcp_get_element(json, i, 0);
		if (((obj->type & JC_OBJ) && json[*i] != '}') ||
			((obj->type & JC_ARR) && json[*i] != ']'))
			ft_error("Bad syntax of JSON");
		++(*i);
		jcp_skip_whitespaces(json, i);
	}
}
