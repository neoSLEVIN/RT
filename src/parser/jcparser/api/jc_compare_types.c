/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_compare_types.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 22:19:29 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/02 22:19:58 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "jc_parser.h"

_Bool	jc_compare_types(const t_jc_field *field, JC_TYPE types)
{
	if (field == NULL)
		ft_error("NPE: field (jc_compare_types)");
	if (field->obj == NULL)
		return (JC_NULL & types);
	return (field->obj->type & types);
}
