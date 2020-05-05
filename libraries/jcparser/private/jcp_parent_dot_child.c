/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_parent_dot_child.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 05:51:21 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/06 00:45:23 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"

char	*jcp_parent_dot_child(const char *parent, const char *child)
{
	char	*result;

	result = ft_strnew(ft_strlen(parent) + 1 + ft_strlen(child));
	if (!result)
		ft_error("Can't allocate memory");
	ft_strcat(result, parent);
	ft_strcat(result, ".");
	ft_strcat(result, child);
	return (result);
}