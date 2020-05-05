/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_free_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 00:27:05 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/03 22:42:46 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"

void	jcp_free_tree(JCP_OBJ **obj)
{
	if (!obj || !*obj)
		return ;
	jcp_free_tree(&(*obj)->next);
	jcp_free_tree(&(*obj)->child);
	jcp_free_tree(&(*obj)->trash);
	if (DEBUG) // TODO DELETE THIS BEFORE DEFENDING
		ft_printf("%s\n", (*obj)->full_name);
	ft_strdel(&(*obj)->full_name);
	ft_memdel((void**)obj);
}
