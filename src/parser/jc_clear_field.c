/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_clear_field.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 02:39:59 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/06 05:39:44 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	jc_clear_field(t_field *field)
{
//	json_object_put(field->obj);
	ft_printf("%s\n", field->full_name);
	ft_strdel(&field->full_name);
}
