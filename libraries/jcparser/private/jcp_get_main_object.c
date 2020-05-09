/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_get_main_object.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"

static void	jcp_calculate_cnt_of_nodes(JCP_OBJ *node, size_t *cnt)
{
	if (node == NULL)
		return ;
	++(*cnt);
	if (node->type & (JC_ARR | JC_OBJ))
		jcp_calculate_cnt_of_nodes(node->child, &node->cnt_of_nodes);
	jcp_calculate_cnt_of_nodes(node->next, cnt);
}

static void	jcp_print_neighbours_error(const char *name, const size_t length)
{
	char	*err_msg;

	if (!(err_msg = ft_strnew(length)))
		ft_error("The same fields under the same entity");
	ft_strncpy(err_msg, name, length);
	ft_printf("Error:\t%s\"%s\"\n",
		"The same fields under the same entity: ", err_msg);
	ft_strdel(&err_msg);
	exit(1);
}

static void	jcp_check_for_same_neighbours(JCP_OBJ *obj)
{
	JCP_OBJ	*temp;

	if (obj == NULL)
		return ;
	temp = obj->next;
	while ((obj->type & JC_ELEM) == 0 && temp != NULL)
	{
		if (obj->name.length == temp->name.length &&
				ft_strnequ(obj->name.start, temp->name.start, obj->name.length))
			jcp_print_neighbours_error(obj->name.start, obj->name.length);
		temp = temp->next;
	}
	jcp_check_for_same_neighbours(obj->child);
	jcp_check_for_same_neighbours(obj->next);
}

JCP_OBJ		*jcp_get_main_object(const char *json)
{
	JCP_OBJ	*main_obj;
	size_t	i;

	i = 0;
	main_obj = jcp_create_t_jcp_object();
	jcp_get_value_of_obj_or_arr(json, &i, main_obj);
	main_obj->value.start = (char*)json;
	if (json[i])
		ft_error("Bad syntax of JSON");
	jcp_check_for_same_neighbours(main_obj->child);
	jcp_calculate_cnt_of_nodes(main_obj->child, &main_obj->cnt_of_nodes);
	return (main_obj);
}
