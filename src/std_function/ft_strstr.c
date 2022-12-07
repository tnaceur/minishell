/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:37:37 by abelkhad          #+#    #+#             */
/*   Updated: 2022/12/01 23:59:16 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_strstr(char *src, char *str)
{
	int	i;
	int	j;

	if (!ft_len(src) || !ft_len(str))
		return (-2);
	i = 0;
	while (src[i])
	{
		j = -1;
		while (src[i + (++j)] && str[j])
		{
			if (src[i + j] != str[j])
				break ;
		}
		if (j == ft_len(str))
			return (1);
		i++;
	}
	return (0);
}

int	ft_strstr_v2(char *str, char *src, int i)
{
	if (!str || !src || i < 0 || i >= ft_len(str))
		return (-1);
	while (str[i])
	{
		if (ft_strchar(src, str[i]) == 1)
			return (i);
		i++;
	}
	return (0);
}
