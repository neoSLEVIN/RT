/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_get_array_length.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 16:43:37 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/03 01:14:17 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "jc_parser.h"

size_t	jc_get_array_length(const t_jc_field *field)
{
	if (jc_compare_types(field, JC_NULL) == TRUE)
		return (0);
	if (jc_compare_types(field, (JC_ARR | JC_OBJ)) == FALSE)
		return (0);
	return (field->obj->cnt_of_nodes);
}
