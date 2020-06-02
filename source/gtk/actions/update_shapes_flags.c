/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shapes_flags.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 21:23:40 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/29 21:23:40 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	update_shapes_flags(_Bool *update_shapes, _Bool *update_property)
{
	*update_shapes = TRUE;
	*update_property = TRUE;
}
