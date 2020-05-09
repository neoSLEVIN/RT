/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   holders_cnt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 19:42:40 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 19:50:53 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	increase_holders_cnt(int *count, _Bool *button)
{
	if (*button == FALSE)
		++(*count);
	*button = TRUE;
}

void	decrease_holders_cnt(int *count, _Bool *button)
{
	if (*button == TRUE)
		--(*count);
	*button = FALSE;
}
