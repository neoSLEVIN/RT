/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_get_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jc_parser.h"

static double	jcp_atof(const char *start, const size_t length)
{
	char	*dot;
	char	*dbl_str;
	double	dbl;
	char	test_str[4];

	ft_strcpy(test_str, "0.1");
	if (!(dbl_str = ft_strnew(length)))
		ft_error("Can't allocate memory");
	ft_strncat(dbl_str, (char*)start, length);
	dot = ft_strchr(dbl_str, '.');
	if (dot != NULL && atof(test_str) != 0.1)
		*dot = ',';
	dbl = atof(dbl_str);
	ft_strdel(&dbl_str);
	return (dbl);
}

static void		jcp_print_error_if_bad_float(double dbl, const char *full_name)
{
	if (dbl < (-MAX_FLOAT) || dbl > (MAX_FLOAT) ||
		(dbl > (-MIN_FLOAT) && dbl < (MIN_FLOAT) && dbl != 0.0))
	{
		ft_printf("Error:\tIncorrect value of float: %s\n%s%s\n",
			full_name,
			"Float value must be in (-MAX_FLOAT; -MIN_FLOAT)",
			" U {0.0} U (MIN_FLOAT; MAX_FLOAT)");
		exit(1);
	}
}

float			jc_get_float_or_default(const JC_FIELD parent,
								const char *child_name, float default_value)
{
	JC_FIELD	dbl_field;
	double		dbl;

	dbl_field = jc_get_field(parent, child_name, (JC_INT | JC_DBL | JC_NULL));
	if (jc_is_null(dbl_field))
		return (default_value);
	dbl = jcp_atof(dbl_field.obj->value.start, dbl_field.obj->value.length);
	jcp_print_error_if_bad_float(dbl, dbl_field.full_name);
	return ((float)dbl);
}

float			jc_get_float_idx(const JC_FIELD parent, const size_t index)
{
	JC_FIELD	dbl_field;
	double		dbl;

	dbl_field = jc_get_field_idx(parent, index, (JC_INT | JC_DBL));
	dbl = jcp_atof(dbl_field.obj->value.start, dbl_field.obj->value.length);
	jcp_print_error_if_bad_float(dbl, dbl_field.full_name);
	return ((float)dbl);
}

float			jc_get_float(const JC_FIELD parent, const char *child_name)
{
	JC_FIELD	dbl_field;
	double		dbl;

	dbl_field = jc_get_field(parent, child_name, (JC_INT | JC_DBL));
	dbl = jcp_atof(dbl_field.obj->value.start, dbl_field.obj->value.length);
	jcp_print_error_if_bad_float(dbl, dbl_field.full_name);
	return ((float)dbl);
}
