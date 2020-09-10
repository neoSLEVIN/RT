/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize_int2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:32:01 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:32:01 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serializer.h"

void	s_int2(t_serializer *s, INT2 num_value)
{
	ft_printf("%[s[%d, %d]", s->fd, "", num_value.x, num_value.y);
}
