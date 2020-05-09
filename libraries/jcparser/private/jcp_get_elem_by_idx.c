/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_get_elem_by_idx.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"

static JCP_OBJ	*jcp_put_to_parent_trash(JCP_OBJ *obj, JCP_OBJ *parent)
{
	JCP_OBJ	*temp;

	obj->type = JC_NULL | JC_ELEM;
	temp = parent->trash;
	parent->trash = obj;
	obj->trash = temp;
	return (obj);
}

JCP_OBJ			*jcp_get_elem_by_idx(const size_t idx, JCP_OBJ *parent)
{
	JCP_OBJ	*obj;

	if (parent == NULL)
		ft_error("NPE: parent (jcp_get_elem_by_idx)");
	if ((parent->type & JC_ARR) == FALSE)
	{
		ft_printf("Error:\tField \"%s\" has object type. %s\n",
			parent->full_name, "Can't find child by index.");
		exit(1);
	}
	if (parent->child == NULL)
		return (jcp_put_to_parent_trash(jcp_create_t_jcp_object(), parent));
	obj = parent->child;
	while (obj != NULL)
	{
		if (obj->name.index == idx)
			return (obj);
		obj = obj->next;
	}
	return (jcp_put_to_parent_trash(jcp_create_t_jcp_object(), parent));
}
