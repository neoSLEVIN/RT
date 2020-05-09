/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_clear_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"
#include "jc_parser.h"

void	jc_clear_all(JC_FIELD json_field)
{
	if (!json_field.obj)
		return ;
	if (ft_strequ(json_field.full_name, "JSON"))
		ft_strdel((char**)&json_field.obj->value.start);
	jcp_free_tree(&json_field.obj);
}
