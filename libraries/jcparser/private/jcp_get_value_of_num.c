/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_get_value_of_num.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"

void	jcp_get_value_of_num(const char *json, size_t *i, JCP_OBJ *obj)
{
	jcp_skip_whitespaces(json, i);
	if (!ft_isdigit(json[*i]) && json[*i] != '-')
		ft_error("Bad syntax of JSON");
	obj->value.start = &json[*i];
	while (ft_isdigit(obj->value.start[obj->value.length]) ||
			obj->value.start[obj->value.length] == '-' ||
			obj->value.start[obj->value.length] == '.')
		++obj->value.length;
	*i += obj->value.length;
	jcp_skip_whitespaces(json, i);
	if (json[*i] != ']' && json[*i] != '}' && json[*i] != ',')
		ft_error("Bad syntax of JSON");
	if (ft_isdigit(*obj->value.start) || *obj->value.start == '-')
		obj->type |= jcp_check_for_number(obj->value.start);
	if ((obj->type & (JC_INT | JC_DBL)) == 0)
		ft_error("Bad syntax of JSON");
	jcp_skip_whitespaces(json, i);
}
