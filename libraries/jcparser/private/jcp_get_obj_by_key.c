/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_get_obj_by_key.c                               :+:      :+:    :+:   */
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

	obj->type = JC_NULL;
	temp = parent->trash;
	parent->trash = obj;
	obj->trash = temp;
	return (obj);
}

JCP_OBJ			*jcp_get_obj_by_key(const char *key, JCP_OBJ *parent)
{
	JCP_OBJ	*obj;

	if (key == NULL)
		ft_error("NPE: key (jcp_get_obj_by_key)");
	if (parent == NULL)
		ft_error("NPE: parent (jcp_get_obj_by_key)");
	if (parent->type & JC_ARR)
	{
		ft_printf("Error:\tField \"%s\" has array type. %s%s%s\n",
			parent->full_name, "Can't find child \"", key, "\" by name.");
		exit(1);
	}
	if (parent->child == NULL)
		return (jcp_put_to_parent_trash(jcp_create_t_jcp_object(), parent));
	obj = parent->child;
	while (obj != NULL)
	{
		if (obj->name.length == ft_strlen(key) &&
				ft_strnequ(obj->name.start, key, obj->name.length))
			return (obj);
		obj = obj->next;
	}
	return (jcp_put_to_parent_trash(jcp_create_t_jcp_object(), parent));
}
