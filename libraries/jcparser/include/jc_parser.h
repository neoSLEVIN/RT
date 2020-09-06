/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JC_PARSER_H
# define JC_PARSER_H

# include "libft.h"
# include "jc_data.h"

/*
** =============================================================================
** =============================== API structure ===============================
** =============================================================================
** ========================= Main Entity in JC parser ==========================
** ========== Contains main JC private entity and full path to field ===========
** =============================================================================
*/
# define JC_FIELD struct s_jc_field

struct		s_jc_field
{
	char	*full_name;
	JCP_OBJ	*obj;
};

/*
** =============================================================================
** =============================== API functions ===============================
** =============================================================================
*/
/*
** ========================== Creation of main object ==========================
*/
JC_FIELD	jc_get_json_field(const char *file_name, size_t max_size);
/*
** ========================= Creation of side objects ==========================
*/
JC_FIELD	jc_get_field(const JC_FIELD parent, const char *field_name,
							JC_TYPE type);
JC_FIELD	jc_get_field_idx(const JC_FIELD parent, const size_t index,
							JC_TYPE type);
/*
** ========================== Cleaning of all objects ==========================
*/
void		jc_clear_all(JC_FIELD json_field);
/*
** ======================== Getters for standard types =========================
*/
_Bool		jc_get_bool(const JC_FIELD parent, const char *child_name);
_Bool		jc_get_bool_or_default(const JC_FIELD parent,
							const char *child_name, _Bool default_value);
char		*jc_get_string(const JC_FIELD parent, const char *child_name,
							_Bool nullable);
char		*jc_get_string_or_default(const JC_FIELD parent,
							const char *child_name, const char *default_string);
float		jc_get_float(const JC_FIELD parent, const char *child_name);
float		jc_get_float_idx(const JC_FIELD parent, const size_t index);
float		jc_get_float_or_default(const JC_FIELD parent,
							const char *child_name, float default_value);
/*
** ============================= Additional utils ==============================
*/
char		*jc_full_name(const JC_FIELD field);
_Bool		jc_compare_types(const JC_FIELD field, const JC_TYPE types);
_Bool		jc_is_null(const JC_FIELD field);
size_t		jc_get_array_length(const JC_FIELD field);

#endif
