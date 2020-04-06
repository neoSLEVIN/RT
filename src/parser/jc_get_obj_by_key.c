/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_get_obj_by_key.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 05:52:59 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/05 05:52:59 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

json_object	*jc_get_obj_by_key(const char *key, const t_field *parent)
{
	json_object	*obj;

	if (!(json_object_object_get_ex(parent->obj, key, &obj))) {
		ft_printf("Error:\t\"%s\" is not found in JSON\n",
			jc_parent_dot_child(parent->full_name, key));
		exit(1);
	}
	return (obj);
}
