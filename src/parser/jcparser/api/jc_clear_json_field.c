/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_clear_json_field.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 00:04:02 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/03 00:04:02 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"
#include "jc_parser.h"

void	jc_clear_json_field(t_jc_field *json_field)
{
	if (ft_strequ(json_field->full_name, "JSON"))
		ft_strdel((char**)&json_field->obj->value.start);
	jcp_free_tree(&json_field->obj);
	ft_printf("%s\n", json_field->full_name);
	ft_strdel(&json_field->full_name);
}
