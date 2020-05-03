/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_free_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 00:27:05 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/13 00:27:05 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"

t_jcp_object	*jcp_free_tree(t_jcp_object **obj)
{
	if (!obj || !*obj)
		return (NULL);
	jcp_free_tree(&(*obj)->next);
	jcp_free_tree(&(*obj)->child);
	ft_memdel((void**)obj);
	return (NULL);
}
