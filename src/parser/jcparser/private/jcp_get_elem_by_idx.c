/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_get_elem_by_idx.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 23:14:24 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/02 23:14:44 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"

t_jcp_object	*jcp_get_elem_by_idx(const size_t idx, const t_jc_field *parent)
{
	t_jcp_object	*obj;

	if (parent == NULL || parent->obj == NULL)
		ft_error("NPE: parent (jcp_get_elem_by_idx)");
	if (parent->obj->child == NULL)
		return (NULL);
	obj = parent->obj->child;
	while (obj != NULL)
	{
		if (obj->name.index == idx)
			return (obj);
		obj = obj->next;
	}
	return (NULL);
}
