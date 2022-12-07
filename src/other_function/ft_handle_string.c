/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:35:53 by abelkhad          #+#    #+#             */
/*   Updated: 2022/12/01 23:57:11 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_nbr_of_char(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str | !(*str))
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	ft_get_next_char(char *str, char *c, int start)
{
	int	i;

	if (!str || (start < 0 && start >= ft_len(str)))
		return (-2);
	i = start;
	while (str[start])
	{
		if (ft_strchar(c, str[start]) == 1 && i != start)
			return (start);
		if (i == start)
		{
			while (ft_isspace(str[start]) == 1 || ft_strchar(c,
					str[start]) == 1)
				start++;
		}
		else
			start++;
	}
	return (start);
}

int	ft_size_help(char *str, int *i)
{
	int	len;
	int	end;
	int	size;

	size = 1;
	end = 0;
	if (!str || !str[0] || *i < 0)
		ft_put_error("ft_size_help string");
	len = ft_strlen(str) - 1;
	if (len == 0 || *i >= len)
	{
		(*i) = len + 1;
		return (-1);
	}
	end = ft_strchar1(str, str[*i], *i);
	if (end <= 0)
		end = len + 1;
	(*i)++;
	size = end - *i;
	return (size);
}
