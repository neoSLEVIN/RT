/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_del.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 01:55:23 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/05 01:56:45 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strsplit_del(char **split)
{
	int	i;

	i = -1;
	if (!split)
		return;
	while (split[++i])
		ft_strdel(&split[i]);
	free(split);
}
