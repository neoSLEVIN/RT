/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 13:01:53 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/02 03:37:56 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

void	check_error_cl(const int num, const char *message, char *path)
{
	if (num)
	{
		ft_printf("Number:\t%d\nError:\t%s\n", num, message);
		if (path)
+			ft_printf("Path:\t%s\n", path);
		exit(1);
	}
}
