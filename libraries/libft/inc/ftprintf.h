/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftprintf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTPRINTF_H
# define FTPRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <wchar.h>

# if defined(__WIN32__)
#  include <stdint.h>
# endif

# define FT_NUM_LENGTH 15000

# define FT_EOC 0
# define FT_RED (1 << 0)
# define FT_GREEN (1 << 1)
# define FT_BLUE (1 << 2)
# define FT_YELLOW (1 << 3)
# define FT_PURPLE (1 << 4)
# define FT_CYAN (1 << 5)

# define FT_SHARP (1 << 0)
# define FT_PLUS (1 << 1)
# define FT_MINUS (1 << 2)
# define FT_SPACE (1 << 3)
# define FT_ZERO (1 << 4)

# define FT_LEN_L (1 << 0)
# define FT_LEN_LL (1 << 1)
# define FT_LEN_BL (1 << 2)
# define FT_LEN_H (1 << 3)
# define FT_LEN_HH (1 << 4)
# define FT_LEN_J (1 << 5)
# define FT_LEN_Z (1 << 6)

typedef struct			s_property
{
	int					color_flg;
	int					fd_flg;
	int					flag;
	int					width;
	int					precision;
	int					length;
	char				type;
}						t_prop;

typedef struct			s_double
{
	long double			ld;
	double				d;
	unsigned char		sign;
	unsigned short		exp;
	unsigned long long	mantissa;
	char				*big;
	char				*little;
	char				*summand;
	char				*temp;
	int					is_inf;
	int					is_nan;
}						t_double;

typedef struct			s_print
{
	char				*cur;
	va_list				args;
	t_prop				prop;
	t_double			num;
	int					len;
	size_t				i;
	int					fd;
}						t_print;

int						pft_is_prop(char *c);
int						pft_is_flag(char *c);
int						pft_is_length(char *c);
int						pft_is_type(char *c);
void					pft_is_inf_nan(t_double *num, _Bool is_long);

int						pft_parser(t_print *print);
void					pft_parse_addition(t_print *print);
void					pft_parse_flag(t_print *print);
void					pft_parse_width(t_print *print);
void					pft_parse_precision(t_print *print);
void					pft_parse_length(t_print *print);
void					pft_parse_type(t_print *print);

void					pft_choose_color(t_print *print);
int						pft_choose_type(t_print *print);

void					pft_print_color(t_print *print, char *color);
void					pft_print_wchar(t_print *print, wchar_t c);
void					pft_print_indent(t_print *print, char c, int cnt);
void					pft_print_abs_integer(intmax_t num, int *len, int fd);
int						pft_print_d(t_print *print);
int						pft_print_u(t_print *print);
int						pft_print_o(t_print *print);
int						pft_print_x(t_print *print);
int						pft_print_f(t_print *print);
int						pft_print_c(t_print *print);
int						pft_print_s(t_print *print);
int						pft_print_p(t_print *print);
int						pft_print_percent(t_print *print);
int						pft_print_other(t_print *print);

void					pft_calculate_f(t_double *num, _Bool is_long);
void					pft_calc_pos_power(char *num, char *temp, int power);
void					pft_calc_neg_power(char *num, char *temp, int power);
void					pft_calculate_sum_big(char *dst, char *src);
void					pft_calculate_sum_little(char *dst, char *src);
void					pft_round_f(t_double *num, int precision);

#endif
