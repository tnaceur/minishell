/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:37:25 by abelkhad          #+#    #+#             */
/*   Updated: 2022/12/01 23:59:50 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_strchar1(char *src, char c, int i)
{
	int	start;

	start = i;
	if (!src || i >= ft_len(src) || i < 0)
		return (-2);
	while (src[i])
	{
		if (src[i] == c && i != start)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_strchar(char *str, char c)
{
	int	i;

	i = -1;
	if (!str || !str[0] || !c)
		return (-1);
	while (str[++i])
	{
		if (str[i] == c)
			return (1);
	}
	return (0);
}

int	ft_strchar2(char *src, char c, int start)
{
	int		i;
	char	ch;

	i = start;
	if (!src || i >= ft_len(src) || i < 0)
		return (-2);
	if (!c)
		return (ft_len(src) - 1);
	while (src[i])
	{
		if (ft_strchar("\"\'", src[i]) == 1 && c == '|')
		{
			ch = src[i++];
			while (src[i] && src[i] != ch)
				i++;
		}
		if (src[i] == c && start != i)
			return (i);
		i++;
	}
	return (-1);
}
