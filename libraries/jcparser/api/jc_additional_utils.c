/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_additional_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jc_parser.h"

char	*jc_full_name(const JC_FIELD field)
{
	return (field.full_name);
}

_Bool	jc_compare_types(const JC_FIELD field, const JC_TYPE types)
{
	if (types == JC_ANY)
		return (TRUE);
	if (field.obj == NULL)
		return (JC_NULL & types);
	return (field.obj->type & types);
}

_Bool	jc_is_null(const JC_FIELD field)
{
	return (jc_compare_types(field, JC_NULL));
}

size_t	jc_get_array_length(const JC_FIELD field)
{
	if (jc_is_null(field))
		return (0);
	if (jc_compare_types(field, (JC_ARR | JC_OBJ)) == FALSE)
		return (0);
	return (field.obj->cnt_of_nodes);
}
