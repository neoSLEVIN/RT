/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_create_t_jcp_object.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"

static void		jcp_init_t_jcp_name(t_jcp_name *name)
{
	name->start = NULL;
	name->length = 0;
	name->index = 0;
	name->empty = '\0';
}

static void		jcp_init_t_jcp_value(t_jcp_value *value)
{
	value->start = NULL;
	value->length = 0;
	value->empty = '\0';
}

JCP_OBJ			*jcp_create_t_jcp_object(void)
{
	JCP_OBJ	*obj;

	if ((obj = (JCP_OBJ*)malloc(sizeof(JCP_OBJ))) == NULL)
		ft_error("Can't allocate memory");
	jcp_init_t_jcp_name(&obj->name);
	jcp_init_t_jcp_value(&obj->value);
	obj->type = 0;
	obj->cnt_of_nodes = 0;
	obj->full_name = NULL;
	obj->child = NULL;
	obj->next = NULL;
	obj->trash = NULL;
	return (obj);
}
