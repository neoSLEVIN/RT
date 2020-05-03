/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_get_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 02:43:35 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/03 02:43:35 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"

t_jcp_object	*jcp_get_object(const char *json, size_t *i)
{
	t_jcp_object	*obj;

	obj = jcp_create_t_jcp_object();
	jcp_get_object_name(json, i, obj);
	if (json[(*i)++] != ':')
		ft_error("Bad syntax of JSON");
	jcp_get_value_by_type(json, i, obj);
	if (json[*i] == ',')
	{
		++(*i);
		obj->next = jcp_get_object(json, i);
	}
	return (obj);
}
