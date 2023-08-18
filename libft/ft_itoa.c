/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkersten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:35:21 by rkersten          #+#    #+#             */
/*   Updated: 2023/04/06 17:01:12 by rkersten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_strlen_itoa(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	ft_fill_str(char *s, int n)
{
	int		i;
	long	j;

	if (n == 0)
	{
		s[0] = '0';
		return ;
	}
	i = ft_strlen_itoa(n) - 1;
	j = (long) n;
	if (j < 0)
	{
		j *= -1;
		s[0] = '-';
	}
	while (i != 0)
	{
		s[i] = j % 10 + 48;
		j /= 10;
		i--;
	}
	if (n > 0)
		s[0] = j % 10 + 48;
}

char	*ft_itoa(int n)
{
	int		i;
	char	*s;

	s = NULL;
	i = ft_strlen_itoa(n);
	s = (char *) malloc(sizeof(*s) * (i + 1));
	if (!s)
		return (NULL);
	ft_fill_str(s, n);
	s[i] = '\0';
	return (s);
}
