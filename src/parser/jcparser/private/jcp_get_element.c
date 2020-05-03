/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_get_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 02:39:57 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/03 02:39:57 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"

t_jcp_object	*jcp_get_element(const char *json, size_t *i,
								const size_t index)
{
	t_jcp_object	*obj;

	obj = jcp_create_t_jcp_object();
	obj->type |= JC_ELEM;
	obj->name.index = index;
	jcp_get_value_by_type(json, i, obj);
	if (json[*i] == ',')
	{
		++(*i);
		obj->next = jcp_get_element(json, i, index + 1);
	}
	return (obj);
}
