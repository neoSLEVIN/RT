/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_str_of_types.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 22:29:07 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/15 22:29:07 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"

char	*jcp_str_of_types(JC_TYPE types)
{
	char	*res;
	size_t	len;

	len = 0;
	(types & JC_NULL) ? len += 5 : 0;
	(types & JC_OBJ) ? len += 7 : 0;
	(types & JC_ARR) ? len += 6 : 0;
	(types & JC_ELEM) ? len += 17 : 0;
	(types & JC_BOOL) ? len += 8 : 0;
	(types & JC_INT) ? len += 8 : 0;
	(types & JC_DBL) ? len += 13 : 0;
	(types & JC_STR) ? len += 7 : 0;
	if (len == 0 || !(res = ft_strnew(len + 1)))
		return (NULL);
	ft_strcat(res, "|");
	(types & JC_NULL) ? ft_strcat(res, "null|") : 0;
	(types & JC_OBJ) ? ft_strcat(res, "object|") : 0;
	(types & JC_ARR) ? ft_strcat(res, "array|") : 0;
	(types & JC_ELEM) ? ft_strcat(res, "element of array|") : 0;
	(types & JC_BOOL) ? ft_strcat(res, "boolean|") : 0;
	(types & JC_INT) ? ft_strcat(res, "integer|") : 0;
	(types & JC_DBL) ? ft_strcat(res, "float/double|") : 0;
	(types & JC_STR) ? ft_strcat(res, "string|") : 0;
	return (res);
}
