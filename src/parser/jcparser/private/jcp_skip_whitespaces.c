/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_skip_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 00:25:32 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/03 02:09:42 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"

void	jcp_skip_whitespaces(const char *str, size_t *index)
{
	if (!str)
		return ;
	while ((str[*index] >= '\t' && str[*index] <= '\r') || str[*index] == ' ')
		++(*index);
}
