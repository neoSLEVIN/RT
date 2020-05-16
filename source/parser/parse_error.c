/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_error(const char *parent_name, const char *child_name,
					const char *cause)
{
	ft_printf("Error:\t");
	if (!parent_name && !child_name && !cause)
		ft_printf("Unknown error");
	else if (!parent_name && !child_name)
		ft_printf("%s", cause);
	else if (!cause && (!parent_name || !child_name))
		ft_printf("\"%s\"", parent_name ? parent_name : child_name);
	else if (!cause)
		ft_printf("\"%s.%s\"", parent_name, child_name);
	else if (!parent_name || !child_name)
		ft_printf("\"%s\": %s", parent_name ? parent_name : child_name, cause);
	else
		ft_printf("\"%s.%s\": %s", parent_name, child_name, cause);
	ft_printf("\n");
	exit(1);
}
