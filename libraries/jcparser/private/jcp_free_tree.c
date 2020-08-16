/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_free_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
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
	ft_strdel(&(*obj)->full_name);
	ft_memdel((void**)obj);
}
