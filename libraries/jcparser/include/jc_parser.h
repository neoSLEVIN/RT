/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 02:19:49 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/03 21:51:52 by cschoen          ###   ########lyon.fr   */
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
*/

/*
** =============================================================================
** ========================= Main Entity in JC parser ==========================
** ========== Contains main JC private entity and full path to field ===========
 * =============================================================================
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
JC_FIELD	jc_get_field(const char *field_name, const JC_FIELD parent,
							JC_TYPE type);
JC_FIELD	jc_get_field_idx(const size_t index, const JC_FIELD parent,
							JC_TYPE type);
/*
** ========================== Cleaning of all objects ==========================
*/
void		jc_clear_all(JC_FIELD json_field);
/*
** ======================== Getters for standard types =========================
*/
char		*jc_get_string(const JC_FIELD parent, const char *child_name,
							_Bool nullable);
float		jc_get_float(const JC_FIELD parent, const char *child_name);
float		jc_get_float_idx(const JC_FIELD parent, const size_t index);
/*
** ============================= Additional utils ==============================
*/
char		*jc_full_name(const JC_FIELD field);
_Bool		jc_compare_types(const JC_FIELD field, const JC_TYPE types);
_Bool		jc_is_null(const JC_FIELD field);
size_t		jc_get_array_length(const JC_FIELD field);

#endif
