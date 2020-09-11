/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_change_off_dots.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amace-ty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 15:07:20 by amace-ty          #+#    #+#             */
/*   Updated: 2020/09/11 15:07:21 by amace-ty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

_Bool	do_change_off_dots(FLT3 *dots, int cnt, int diff)
{
	cl_float	coeff;
	FLT3		new_distance;
	int			i;
	_Bool		do_change;

	do_change = FALSE;
	coeff = (cl_float)diff * ((cl_float)diff + 0.15f);
	i = -1;
	while (++i < cnt)
	{
		new_distance = v3_scale(dots[i], coeff);
		if (v3_length(new_distance) < 0.01f && coeff < 1.0f)
			continue ;
		do_change = TRUE;
		dots[i] = new_distance;
	}
	return (do_change);
}
