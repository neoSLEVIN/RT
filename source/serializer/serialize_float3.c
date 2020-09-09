/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize_float3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:31:57 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:31:58 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serializer.h"

void	s_float3(t_serializer *s, FLT3 num_value)
{
	ft_printf("%[s[%.3f, %.3f, %.3f]", s->fd, "",
				num_value.x, num_value.y, num_value.z);
}
