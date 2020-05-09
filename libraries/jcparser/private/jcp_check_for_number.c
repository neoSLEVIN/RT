/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_check_for_number.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"

static int		jcp_check_for_valid_dot_and_sign(const char *value,
												const size_t length)
{
	size_t	i;
	int		dot_cnt;

	dot_cnt = 0;
	if (length == 0)
		return (-1);
	if (length == 1 && *value == '-')
		return (-1);
	i = (*value == '-') ? 1 : 0;
	if (value[i] == '.' || value[length - 1] == '.')
		return (-1);
	while (++i < length)
	{
		if (value[i] == '-')
			return (-1);
		if (value[i] == '.')
			++dot_cnt;
		if (dot_cnt > 1)
			return (-1);
	}
	return (dot_cnt);
}

static JC_TYPE	jcp_check_for_integer(const char *value, size_t length)
{
	size_t	i;

	i = (*value == '-') ? 1 : 0;
	(*value == '-') ? --length : 0;
	if (length > 10)
		return (0);
	if (length < 10)
		return (JC_INT);
	if (*value == '-')
		return (ft_strncmp(&value[i], "2147483648", 10) > 0 ? 0 : JC_INT);
	return (ft_strncmp(&value[i], "2147483647", 10) > 0 ? 0 : JC_INT);
}

JC_TYPE			jcp_check_for_number(const char *value)
{
	size_t	i;
	size_t	length;
	int		dot_cnt;
	JC_TYPE	type;

	length = 0;
	while (ft_isdigit(value[length]) ||
			value[length] == '-' || value[length] == '.')
		++length;
	if (length == 0)
		return (0);
	if ((dot_cnt = jcp_check_for_valid_dot_and_sign(value, length)) == -1)
		return (0);
	i = (*value == '-') ? 1 : 0;
	if (length > i + 1 && value[i] == '0' && ft_isdigit(value[i + 1]))
		return (0);
	type = JC_DBL;
	if (dot_cnt == 0)
		type |= jcp_check_for_integer(value, length);
	return (type);
}
