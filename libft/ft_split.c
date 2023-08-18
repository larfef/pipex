/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkersten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:05:44 by rkersten          #+#    #+#             */
/*   Updated: 2023/04/13 14:59:36 by rkersten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static	size_t	len_word(const char *s, char c)
{
	size_t	i;

	i = 0;
	if (*s != '\0')
	{
		while (*s == c && *s != '\0')
			s++;
		while (*s != c && *s != '\0')
		{
			i++;
			s++;
		}
	}
	return (i);
}

static size_t	ft_len_tab(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (*s != '\0')
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s != c && *s != '\0')
			i++;
		while (*s != c && *s != '\0')
			s++;
	}
	return (i);
}

static	char	*fill_word(const char *s, char c, char *str)
{
	if (*s != '\0')
	{
		while (*s == c && *s != '\0')
			s++;
		while (*s != c && *s != '\0')
		{
			*str = *s;
			s++;
			str++;
		}
		*str = '\0';
	}
	return ((char *)s);
}

static	int	create_word(const char *s, char c, char **tab, size_t i)
{
	size_t	j;
	size_t	k;

	j = 0;
	while (i--)
	{
		k = len_word(s, c);
		tab[j] = (char *) malloc(sizeof(**tab) * (k + 1));
		if (!tab[j])
		{
			while (j--)
				free(tab[j]);
			free(tab);
			return (0);
		}
		s = fill_word(s, c, tab[j]);
		j++;
	}
	return (1);
}	

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	i;

	tab = NULL;
	if (!s)
		return (NULL);
	i = ft_len_tab(s, c);
	tab = (char **) malloc(sizeof(*tab) * (i + 1));
	if (!tab)
		return (NULL);
	if (!create_word(s, c, tab, i))
		return (NULL);
	tab[i] = NULL;
	return (tab);
}
