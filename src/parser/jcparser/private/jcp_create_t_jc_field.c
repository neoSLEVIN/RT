/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_create_t_jc_field.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 00:17:17 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/13 00:17:17 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"

t_jc_field	jcp_create_t_jc_field(void)
{
	t_jc_field	field;

	field.obj = NULL;
	field.full_name = NULL;
	return (field);
}
