/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_get_obj_by_key.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 05:52:59 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/02 23:10:30 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"

t_jcp_object	*jcp_get_obj_by_key(const char *key, const t_jc_field *parent)
{
	t_jcp_object	*obj;

	if (key == NULL)
		ft_error("NPE: key (jcp_get_obj_by_key)");
	if (parent == NULL || parent->obj == NULL)
		ft_error("NPE: parent (jcp_get_obj_by_key)");
	if (parent->obj->child == NULL)
		return (NULL);
	obj = parent->obj->child;
	while (obj != NULL)
	{
		if (ft_strnequ(obj->name.start, key, ft_strlen(key)))
			return (obj);
		obj = obj->next;
	}
	return (NULL);
}
