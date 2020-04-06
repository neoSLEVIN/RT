/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_field_with_index.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 16:35:58 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/05 16:35:58 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*jc_field_with_index(const char *field, const int index)
{
	char	*index_str;
	char	*result;

	if (!(index_str = ft_itoa(index)))
		ft_error("Can't allocate memory in parsing");
	result = ft_strnew(ft_strlen(field) + 2 + ft_strlen(index_str));
	if (!result)
		ft_error("Can't allocate memory in parsing");
	ft_strcat(result, field);
	ft_strcat(result, "[");
	ft_strcat(result, index_str);
	ft_strcat(result, "]");
	ft_strdel(&index_str);
	return (result);
}
