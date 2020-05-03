/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 02:56:26 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/03 03:02:39 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef JCP_PARSER_H
#define JCP_PARSER_H

# include "libft.h"
# include "jc_data.h"

/*
** ===================== Private functions =====================
*/
t_jcp_object	*jcp_get_obj_by_key(const char *key, const t_jc_field *parent);
t_jcp_object	*jcp_get_elem_by_idx(const size_t idx,
									const t_jc_field *parent);

t_jc_field		jcp_create_t_jc_field(void);
t_jcp_object	*jcp_create_t_jcp_object(void);

t_jcp_object	*jcp_get_main_object(const char *json);
t_jcp_object	*jcp_get_object(const char *json, size_t *i);
t_jcp_object	*jcp_get_element(const char *json, size_t *i,
								const size_t index);

void			jcp_get_object_name(const char *json, size_t *i,
								t_jcp_object *obj);
void			jcp_get_value_by_type(const char *json, size_t *i,
								t_jcp_object *obj);

void			jcp_get_value_of_obj_or_arr(const char *json, size_t *i,
								t_jcp_object *obj);
void			jcp_get_value_of_null(const char *json, size_t *i,
								t_jcp_object *obj);
void			jcp_get_value_of_bool(const char *json, size_t *i,
								t_jcp_object *obj);
void			jcp_get_value_of_str(const char *json, size_t *i,
								t_jcp_object *obj);
void			jcp_get_value_of_num(const char *json, size_t *i,
								t_jcp_object *obj);
JC_TYPE			jcp_check_for_number(const char *value);

t_jcp_object	*jcp_free_tree(t_jcp_object **obj);

void			jcp_skip_whitespaces(const char *str, size_t *index);
char			*jcp_parent_dot_child(const char *parent, const char *child);
char			*jcp_field_with_index(const char *field, const int index);

#endif
