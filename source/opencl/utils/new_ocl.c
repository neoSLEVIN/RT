/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_ocl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

void	new_ocl(t_ocl **ocl)
{
	if (!(*ocl = (t_ocl*)malloc(sizeof(t_ocl))))
		ft_error("Can't allocate memory");
	ft_printf("%{}s\n", FT_YELLOW, "(0%) OpenCL: Initialization");
	init_ocl(*ocl);
	ft_printf("%{}s\n", FT_YELLOW, "(33%) OpenCL: Getting data");
	create_cl(*ocl);
	ft_printf("%{}s\n", FT_YELLOW, "(66%) OpenCL: Compiling");
	compile_cl(*ocl);
	ft_printf("%{}s\n", FT_GREEN, "(100%) OpenCL: All done");
}
