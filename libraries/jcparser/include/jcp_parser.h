/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/15 22:22:51 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JCP_PARSER_H
# define JCP_PARSER_H

# include "libft.h"
# include "jc_data.h"

/*
** =============================================================================
** ============================= Private functions =============================
** =============================================================================
*/
/*
** =============================== Create object ===============================
*/
JCP_OBJ	*jcp_get_main_object(const char *json);
JCP_OBJ	*jcp_get_object(const char *json, size_t *i);
JCP_OBJ	*jcp_get_element(const char *json, size_t *i, const size_t index);
/*
** ========================== Default initialization ===========================
*/
JCP_OBJ	*jcp_create_t_jcp_object(void);
/*
** ============================ Name initialization ============================
*/
void	jcp_get_object_name(const char *json, size_t *i, JCP_OBJ *obj);
/*
** =========================== Value initialization ============================
*/
void	jcp_get_value_by_type(const char *json, size_t *i, JCP_OBJ *obj);
void	jcp_get_value_of_obj_or_arr(const char *json, size_t *i, JCP_OBJ *obj);
void	jcp_get_value_of_null(const char *json, size_t *i, JCP_OBJ *obj);
void	jcp_get_value_of_bool(const char *json, size_t *i, JCP_OBJ *obj);
void	jcp_get_value_of_str(const char *json, size_t *i, JCP_OBJ *obj);
void	jcp_get_value_of_num(const char *json, size_t *i, JCP_OBJ *obj);
JC_TYPE	jcp_check_for_number(const char *value);
/*
** ================================== Getters ==================================
*/
JCP_OBJ	*jcp_get_obj_by_key(const char *key, JCP_OBJ *parent);
JCP_OBJ	*jcp_get_elem_by_idx(const size_t idx, JCP_OBJ *parent);
/*
** ============================= Clear all objects =============================
*/
void	jcp_free_tree(JCP_OBJ **obj);
/*
** ============================= Additional utils ==============================
*/
void	jcp_skip_whitespaces(const char *str, size_t *index);
char	*jcp_parent_dot_child(const char *parent, const char *child);
char	*jcp_field_with_index(const char *field, const int index);
char	*jcp_str_of_types(JC_TYPE types);
void	jcp_print_bad_type_error(const JCP_OBJ *obj, JC_TYPE allowed_types);
void	jcp_print_bad_parent_type_error(const JCP_OBJ *obj,
										JC_TYPE allowed_types);

#endif
