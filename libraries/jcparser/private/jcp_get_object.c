/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_get_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"

JCP_OBJ	*jcp_get_object(const char *json, size_t *i)
{
	JCP_OBJ	*obj;

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
