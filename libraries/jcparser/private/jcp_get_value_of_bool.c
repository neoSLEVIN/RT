/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_get_value_of_bool.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"

void	jcp_get_value_of_bool(const char *json, size_t *i, JCP_OBJ *obj)
{
	jcp_skip_whitespaces(json, i);
	if (ft_strncmp(&json[*i], "false", 5) && ft_strncmp(&json[*i], "true", 4))
		ft_error("Bad syntax of JSON");
	obj->type |= JC_BOOL;
	obj->value.start = &json[*i];
	obj->value.length = (json[*i] == 'f') ? 5 : 4;
	*i += (json[*i] == 'f') ? 5 : 4;
	jcp_skip_whitespaces(json, i);
}
