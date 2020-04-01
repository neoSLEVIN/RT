/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrsplit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 09:23:33 by cschoen           #+#    #+#             */
/*   Updated: 2019/07/14 13:32:53 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_free(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		ft_strdel(&split[i]);
	free(split);
}

static size_t	ft_wordsize(const char *s, const char *re)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (*s && *s != re[i])
	{
		i = 0;
		while (re[i] && *s != re[i])
			++i;
		!re[i] ? ++s : 0;
		!re[i] ? ++len : 0;
	}
	return (len);
}

static void		ft_makesplit(char const *s, char const *re, char **split)
{
	int	ind;
	int	len;
	int	i;

	ind = 0;
	while (*s)
	{
		i = -1;
		while (re[++i])
			while (*s == re[i] && s++)
				i = 0;
		if ((len = ft_wordsize(s, re)) != 0)
		{
			if (!(split[ind] = ft_strnew(len)))
				return (ft_free(split));
			ft_strncpy(split[ind++], s, len);
		}
		s += len;
	}
	split[ind] = NULL;
}

char			**ft_strstrsplit(char const *s, char const *re)
{
	char	**split;
	int		words;

	if (!s || !re)
		return (NULL);
	words = ft_wordcnt(s, re);
	if (!(split = (char **)malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	ft_makesplit(s, re, split);
	return (split);
}
