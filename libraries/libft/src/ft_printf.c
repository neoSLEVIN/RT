/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		pft_free_print(t_print *print)
{
	ft_strdel(&print->num.big);
	ft_strdel(&print->num.little);
	ft_strdel(&print->num.summand);
	ft_strdel(&print->num.temp);
	return (0);
}

static _Bool	pft_is_here_num(const char *format)
{
	size_t	i;
	char	c;

	i = -1;
	while (format[++i])
		if (format[i] == '%')
		{
			++i;
			while (format[i] == '{' || format[i] == '}' ||
				format[i] == '[' || format[i] == ']')
				++i;
			c = (char)format[i];
			while (pft_is_prop(&c))
			{
				++i;
				c = (char)format[i];
			}
			if (format[i] == 'f' || format[i] == 'F')
				return (1);
		}
	return (0);
}

static int		pft_init_num_text(t_print *print)
{
	if (!(print->num.big = ft_strnew(FT_NUM_LENGTH)))
		return (pft_free_print(print));
	if (!(print->num.little = ft_strnew(FT_NUM_LENGTH)))
		return (pft_free_print(print));
	if (!(print->num.summand = ft_strnew(FT_NUM_LENGTH)))
		return (pft_free_print(print));
	if (!(print->num.temp = ft_strnew(FT_NUM_LENGTH)))
		return (pft_free_print(print));
	*print->num.big = '0';
	*print->num.little = '0';
	*print->num.summand = '0';
	*print->num.temp = '0';
	return (1);
}

static int		pft_init_print(t_print *print, const char *format)
{
	print->cur = (char*)format;
	print->fd = 1;
	print->len = 0;
	print->i = 0;
	print->prop.color_flg = 0;
	print->prop.fd_flg = 0;
	print->prop.flag = 0;
	print->prop.width = 0;
	print->prop.precision = -1;
	print->prop.length = 0;
	print->prop.type = '\0';
	print->num.ld = 0;
	print->num.d = 0;
	print->num.sign = 0;
	print->num.exp = 0;
	print->num.mantissa = 0;
	print->num.is_inf = 0;
	print->num.is_nan = 0;
	print->num.big = NULL;
	print->num.little = NULL;
	print->num.summand = NULL;
	print->num.temp = NULL;
	if (pft_is_here_num(format))
		return (pft_init_num_text(print));
	return (1);
}

int				ft_printf(const char *format, ...)
{
	t_print	print;

	if (!format)
		return (-1);
	va_start(print.args, format);
	if (!pft_init_print(&print, format))
		return (-1);
	return (pft_parser(&print));
}
