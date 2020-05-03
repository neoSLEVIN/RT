/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 02:19:49 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/03 03:32:08 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef JC_PARSER_H
#define JC_PARSER_H

# ifdef __APPLE__
#  include "OpenCL/opencl.h"
# else
#  include "CL/cl.h"
# endif

# include "libft.h"
# include "jc_data.h"

/*
** ===================== API functions =====================
*/
t_jc_field				jc_get_json_field(const char *file_name,
										size_t max_size);
t_jc_field				jc_get_field(const char *field_name,
										const t_jc_field *parent, JC_TYPE type);
t_jc_field				jc_get_field_idx(const size_t index,
										const t_jc_field *parent, JC_TYPE type);

char					*jc_get_string(const t_jc_field *parent,
										const char *child_name, _Bool nullable);
float					jc_get_float(const t_jc_field *parent,
										const char *child_name);
float					jc_get_float_idx(const t_jc_field *parent,
										const size_t index);
cl_float3				jc_get_cl_float3(const t_jc_field *parent,
										const char *child_name);

void					jc_clear_json_field(t_jc_field *json_field);
void					jc_clear_field(t_jc_field *field);

_Bool					jc_compare_types(const t_jc_field *field,
										JC_TYPE types);
size_t					jc_get_array_length(const t_jc_field *field);

#endif
