/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 21:11:24 by abelkhad          #+#    #+#             */
/*   Updated: 2022/12/04 00:00:36 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_check_engine(char *str, int *i)
{
	if (str[*i] == '\"' || str[*i] == '\'')
	{
		if (ft_check_h3(str, i, 1) == -1)
			return (-1);
	}
	else if (str[*i] == '|')
	{
		if (ft_check_h3(str, i, 0) == -1)
			return (-1);
	}
	else if (ft_strchar("><", str[*i]) == 1)
	{
		if (ft_check_h2(str, i) == -1)
			return (-1);
	}
	else if (str[*i])
		(*i)++;
	return (0);
}

int	ft_check_h(char *str, int start)
{
	char	*tmp;
	int		v;

	v = start;
	while (str[start] && ft_isspace(str[start]))
		start++;
	if (!str[start])
		return (ft_print_syntax_error(0, &str[v - 1]));
	tmp = ft_substr(str, start, ft_len(str) - start);
	v = 0;
	if (!tmp || !tmp[0])
		return (ft_print_syntax_error(0, &str[start - 1]));
	else
	{
		v = ft_check(tmp);
		free(tmp);
		return (v);
	}
	free(tmp);
	return (0);
}

int	ft_check(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	while (str[i])
		if (ft_check_engine(str, &i) == -1)
			return (-1);
	return (0);
}

int	ft_check_h2(char *str, int *i)
{
	char	c;

	c = str[*i];
	(*i)++;
	if (ft_strchar("><", str[*i]) == 1)
	{
		if (str[*i] == c)
		{
			(*i)++;
			while (ft_isspace(str[*i]))
				(*i)++;
			if (ft_strchar("<>|;&", str[*i]) == 1 || str[*i] == 0)
				return (ft_print_syntax_error(0, &str[*i]));
		}
		else
			return (ft_print_syntax_error(0, &str[*i]));
	}
	else
	{
		while (ft_isspace(str[*i]))
			(*i)++;
		if (ft_strchar("><|;&", str[*i]) == 1 || str[*i] == 0)
			return (ft_print_syntax_error(0, &str[*i]));
	}
	return (0);
}

int	ft_check_h3(char *str, int *i, int swt)
{
	int	end;

	if (swt)
	{
		end = ft_strchar2(str, str[*i], *i) + 1;
		if (end <= 0)
			return (ft_print_syntax_error(-1, &str[*i]));
		else
			*i = end;
	}
	else
	{
		end = *i;
		while (end >= 0 && ft_isspace(str[*i]))
			end--;
		if (end <= 0)
			return (ft_print_syntax_error(0, &str[*i]));
		(*i)++;
		if (str[*i] == '|')
			return (ft_print_syntax_error(0, &str[(*i) - 1]));
		else if (ft_check_h(str, *i) == -1)
			return (-1);
	}
	return (0);
}
