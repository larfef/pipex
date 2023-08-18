/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkersten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:41:21 by rkersten          #+#    #+#             */
/*   Updated: 2023/04/06 17:12:48 by rkersten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static	int	is_char_in_set(char c, char const *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static	size_t	check_len_str(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i] != '\0' && is_char_in_set(s1[i], set))
		i++;
	if (i == ft_strlen(s1))
		return (0);
	j = ft_strlen(s1) - 1;
	while (is_char_in_set(s1[j], set))
		j--;
	j++;
	return (j - i);
}

static	void	str_cpy(char const *s1, char const *set, char *new)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (is_char_in_set(s1[i], set))
		i++;
	j = 0;
	while (j != check_len_str(s1, set))
	{
		new[j] = s1[i + j];
		j++;
	}
	if (check_len_str(s1, set))
		new[j] = '\0';
	else
		new[0] = '\0';
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;

	new = NULL;
	if (!s1 || !set)
		return (NULL);
	new = (char *) malloc(sizeof(*new) * (check_len_str(s1, set) + 1));
	if (!new)
		return (NULL);
	str_cpy(s1, set, new);
	return (new);
}
