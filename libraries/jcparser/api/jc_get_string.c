/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_get_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jc_parser.h"

char	*jc_get_string(const JC_FIELD parent, const char *child_name,
						_Bool nullable)
{
	JC_FIELD	str_field;
	char		*str;
	JC_TYPE		type;

	type = JC_STR;
	if (nullable)
		type |= JC_NULL;
	str_field = jc_get_field(parent, child_name, type);
	if (nullable && jc_is_null(str_field))
		return (NULL);
	if (!(str = ft_strnew(str_field.obj->value.length)))
		ft_error("Can't allocate memory");
	ft_strncat(str, (char*)str_field.obj->value.start,
		str_field.obj->value.length);
	return (str);
}

char	*jc_get_string_or_default(const JC_FIELD parent, const char *child_name,
					const char *default_string)
{
	JC_FIELD	str_field;
	char		*str;

	str_field = jc_get_field(parent, child_name, (JC_STR | JC_NULL));
	if (jc_is_null(str_field))
	{
		if (!default_string)
			return (NULL);
		if (!(str = ft_strdup(default_string)))
			ft_error("Can't allocate memory");
		return (str);
	}
	if (!(str = ft_strnew(str_field.obj->value.length)))
		ft_error("Can't allocate memory");
	ft_strncat(str, (char*)str_field.obj->value.start,
			str_field.obj->value.length);
	return (str);
}
