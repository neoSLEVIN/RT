/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_create_t_jcp_object.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 00:19:34 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/03 02:55:26 by cschoen          ###   ########lyon.fr   */
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

t_jcp_object	*jcp_create_t_jcp_object(void)
{
	t_jcp_object	*obj;

	if ((obj = (t_jcp_object*)malloc(sizeof(t_jcp_object))) == NULL)
		ft_error("Can't allocate memory");
	jcp_init_t_jcp_name(&obj->name);
	jcp_init_t_jcp_value(&obj->value);
	obj->type = 0;
	obj->cnt_of_nodes = 0;
	obj->child = NULL;
	obj->next = NULL;
	return (obj);
}
