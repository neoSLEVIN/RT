/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 21:23:40 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/29 21:23:40 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	update_flags(_Bool *update_property1, _Bool *update_property2)
{
	*update_property1 = TRUE;
	*update_property2 = TRUE;
}
