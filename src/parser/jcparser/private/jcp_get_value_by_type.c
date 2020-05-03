/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_get_value_by_type.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 02:37:00 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/03 02:37:00 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"

void	jcp_get_value_by_type(const char *json, size_t *i, t_jcp_object *obj)
{
	jcp_skip_whitespaces(json, i);
	if (json[*i] == '{' || json[*i] == '[')
		jcp_get_value_of_obj_or_arr(json, i, obj);
	else if (json[*i] == 't' || json[*i] == 'f')
		jcp_get_value_of_bool(json, i, obj);
	else if (json[*i] == 'n')
		jcp_get_value_of_null(json, i, obj);
	else if (ft_isdigit(json[*i]) || json[*i] == '-')
		jcp_get_value_of_num(json, i, obj);
	else if (json[*i] == '"')
		jcp_get_value_of_str(json, i, obj);
	else
		ft_error("Bad syntax of JSON");
	jcp_skip_whitespaces(json, i);
}
