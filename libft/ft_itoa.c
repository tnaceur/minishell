/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:31:23 by tnaceur           #+#    #+#             */
/*   Updated: 2021/11/18 09:39:40 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_numcount(int n)
{
	int				size;
	unsigned int	a;

	size = 0;
	a = 0;
	if (n < 0)
	{
		a = -n;
		size++;
	}
	else
	{
		a = n;
	}
	while (a > 0)
	{
		a = a / 10;
		size++;
	}
	return (size);
}

static char	*ft_fill(char *str, int n, int size)
{
	unsigned int	num;

	if (!str)
		return (NULL);
	str[size] = '\0';
	size--;
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (n < 0)
	{
		str[0] = '-';
		num = -n;
	}
	else
		num = n;
	while (num > 0)
	{
		str[size--] = (num % 10) + '0';
		num = num / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				size;

	size = ft_numcount(n);
	if (n == 0)
		size += 1;
	str = (char *)malloc(sizeof(char) * (size + 1));
	str = ft_fill(str, n, size);
	return (str);
}
