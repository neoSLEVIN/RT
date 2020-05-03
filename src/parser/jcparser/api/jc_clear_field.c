/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_clear_field.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 02:39:59 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/12 18:46:47 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "jc_parser.h"

void	jc_clear_field(t_jc_field *field)
{
	ft_printf("%s\n", field->full_name);
	ft_strdel(&field->full_name);
}
