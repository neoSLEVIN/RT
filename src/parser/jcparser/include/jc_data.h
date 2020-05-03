/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_data.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 02:57:25 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/03 03:00:10 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef JC_DATA_H
#define JC_DATA_H

/*
** ===================== Float limits =====================
*/
# define MAX_FLOAT 1.0e+9
# define MIN_FLOAT 1.0e-9

/*
** ===================== Object types =====================
*/
# define JC_TYPE int
# define JC_NULL (1 << 0)
# define JC_OBJ (1 << 1)
# define JC_ARR (1 << 2)
# define JC_ELEM (1 << 3)
# define JC_BOOL (1 << 4)
# define JC_INT (1 << 5)
# define JC_DBL (1 << 6)
# define JC_STR (1 << 7)

/*
** ===================== Private structures =====================
*/
typedef struct			s_jcp_name
{
	const char			*start;
	size_t				length;
	size_t				index;
	char				empty;
}						t_jcp_name;

typedef struct			s_jcp_value
{
	const char			*start;
	size_t				length;
	char				empty;
}						t_jcp_value;

typedef struct			s_jcp_object
{
	t_jcp_name			name;
	t_jcp_value			value;
	JC_TYPE				type;
	size_t				cnt_of_nodes;
	struct s_jcp_object	*child;
	struct s_jcp_object	*next;
}						t_jcp_object;

/*
** ===================== API structure =====================
*/
typedef struct			s_jc_field
{
	char				*full_name;
	t_jcp_object		*obj;
}						t_jc_field;

#endif
