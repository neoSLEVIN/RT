/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   holders_cnt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 19:42:40 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/14 13:06:38 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	increase_holders_cnt(int *count, _Bool *button, t_rt *rt)
{
	if (*button == FALSE)
	{
		*button = TRUE;
		++(*count);
		make_action(rt);
	}
}

void	decrease_holders_cnt(int *count, _Bool *button)
{
	if (*button == TRUE)
	{
		*button = FALSE;
		--(*count);
	}
}
