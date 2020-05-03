/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_get_value_of_null.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 02:31:57 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/03 02:31:57 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"

void	jcp_get_value_of_null(const char *json, size_t *i, t_jcp_object *obj)
{
	jcp_skip_whitespaces(json, i);
	if (ft_strncmp(&json[*i], "null", 4))
		ft_error("Bad syntax of JSON");
	obj->type |= JC_NULL;
	obj->value.start = &json[*i];
	obj->value.length = 4;
	*i += 4;
	jcp_skip_whitespaces(json, i);
}
