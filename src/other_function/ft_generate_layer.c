/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_layer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:36:44 by abelkhad          #+#    #+#             */
/*   Updated: 2022/12/03 20:34:49 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_helper_gen(char *str, char *s_str, char *c, int *i)
{
	char	ch;

	if (str[*i] == '\'' || str[*i] == '\"')
	{
		ch = str[*i];
		while (str[(*i)])
		{
			(*i)++;
			if (ft_strchar(c, str[*i]) == 1)
				s_str[*i] = '@';
			if (str[*i] == ch)
			{
				(*i)++;
				break ;
			}
		}
		return (1);
	}
	else
		return (0);
}

void	ft_generate_layer(char *str, char *s_str, char *c)
{
	int	i;

	i = 0;
	if (!str || !s_str)
		ft_put_error("ft_generate_layer: cannot generate layer");
	while (str[i])
	{
		if (ft_strchar("><", str[i]) == 1)
		{
			i++;
			ft_helper_gen(str, s_str, c, &i);
			while (ft_isspace(str[i]) == 1)
				i++;
			while (str[i])
			{
				if (ft_strchar("> \t<", str[i]) == 1)
					break ;
				i++;
			}
		}
		else if (ft_helper_gen(str, s_str, c, &i) == 0)
			s_str[i++] = '#';
	}
}

void	ft_helper_gen2(char *str, char *s_str, int *i)
{
	s_str[(*i)++] = '#';
	while (ft_isspace(str[*i]))
		s_str[(*i)++] = '#';
	while (str[(*i)])
	{
		if (ft_strchar("< \t>", str[(*i)]) == 1)
			break ;
		s_str[(*i)++] = '#';
	}
}

void	ft_r_generate_layer(char *str, char *s_str)
{
	int	i;

	i = 0;
	if (!str || !s_str || !str[0] || !s_str[0])
		ft_put_error("ft_rev_generate_layer: cannot generate layer");
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			ft_helper_gen(str, s_str, "#", &i);
		else if (ft_isspace(str[i]))
			s_str[i++] = '#';
		else if (str[i] == '#')
			s_str[i++] = '@';
		else if (ft_strchar("><", str[i]) == 1)
			ft_helper_gen2(str, s_str, &i);
		else
			i++;
	}
}
