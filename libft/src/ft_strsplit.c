/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 15:55:48 by cschoen           #+#    #+#             */
/*   Updated: 2019/10/09 09:46:08 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_elements(char const *s, char c)
{
	size_t	num;

	num = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		while (*s && *s != c)
			s++;
		num++;
	}
	if (*(s - 1) != c)
		num++;
	return (num);
}

static size_t	ft_len(char const *s, char c)
{
	size_t	num;

	num = 0;
	while (*s && *s++ != c)
		num++;
	return (num);
}

static void		ft_arrfree(char **arr, size_t count_to_free)
{
	arr--;
	while (count_to_free--)
	{
		free(*arr);
		if (count_to_free)
			arr--;
	}
	free(arr);
	arr = NULL;
}

static void		ft_arrcreate(char **arr, char const *s, char c)
{
	size_t	count_to_free;

	count_to_free = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			break ;
		if ((*arr = ft_strnew(ft_len(s, c))) == NULL)
		{
			ft_arrfree(arr, count_to_free);
			break ;
		}
		count_to_free++;
		ft_strncpy(*arr, s, ft_len(s, c));
		while (*s && *s != c)
			s++;
		arr++;
	}
	if (*s == '\0')
		*arr = NULL;
}

char			**ft_strsplit(char const *s, char c)
{
	char	**arr;

	arr = NULL;
	if (s == NULL)
		return (NULL);
	if ((arr = (char **)malloc(sizeof(char *) * ft_elements(s, c))) == NULL)
		return (NULL);
	ft_arrcreate(arr, s, c);
	return (arr);
}
