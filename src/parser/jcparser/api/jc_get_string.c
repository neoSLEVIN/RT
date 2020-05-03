/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_get_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 03:28:32 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/03 03:40:09 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "jc_parser.h"

char	*jc_get_string(const t_jc_field *parent, const char *child_name,
						_Bool nullable)
{
	t_jc_field	str_field;
	char		*str;
	JC_TYPE		type;

	type = JC_STR;
	if (nullable)
		type |= JC_NULL;
	str_field = jc_get_field(child_name, parent, type);
	if (nullable && jc_compare_types(&str_field, JC_NULL))
	{
		jc_clear_field(&str_field);
		return (NULL);
	}
	if (!(str = ft_strnew(str_field.obj->value.length)))
		ft_error("Can't allocate memory");
	ft_strncat(str, (char*)str_field.obj->value.start,
		str_field.obj->value.length);
	jc_clear_field(&str_field);
	return (str);
}
