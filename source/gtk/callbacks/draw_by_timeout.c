/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_by_timeout.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 02:42:24 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/16 00:59:19 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

int	draw_by_timeout(gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	if (rt->info->update == TRUE || rt->info->keyhold_cnt != 0)
	{
		rt->info->update = FALSE;
		make_action(rt);
		draw_image(rt);
	}
	return (TRUE);
}
