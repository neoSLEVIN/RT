/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_get_json_field.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 05:45:33 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/02 16:06:18 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"
#include "jc_parser.h"

t_jc_field	jc_get_json_field(const char *file_name, size_t max_size)
{
	char		*parsed_text;
	t_jc_field	json_field;

	json_field = jcp_create_t_jc_field();
	parsed_text = ft_get_text_file(file_name, max_size);
	json_field.obj = jcp_get_main_object(parsed_text);
	if (!(json_field.full_name = ft_strdup("JSON")))
		ft_error("Can't allocate memory");
	return (json_field);
}
