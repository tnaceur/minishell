/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:53:21 by abelkhad          #+#    #+#             */
/*   Updated: 2022/12/04 23:16:23 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_get_flag(char c, int type_quote)
{
	if ((type_quote == 1 || type_quote == 0) && c == '\"')
		return (DQ);
	if ((type_quote == 2 || type_quote == 0) && c == '\'')
		return (SQ);
	if (c == '<')
		return (IN_R);
	if (c == '>')
		return (OUT_R);
	if (c == '#')
		return (HCH);
	if (c == ' ')
		return (SPC);
	if (c == '\t')
		return (TABS);
	return ((int)c);
}

void	ft_flag_help(char *str, char *s_str, int *i)
{
	char	c;
	int		quote_type;

	if (!str || !s_str)
		return ;
	c = str[*i];
	if (c == '\'')
		quote_type = 1;
	else if (c == '\"')
		quote_type = 2;
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == c)
			break ;
		s_str[*i] = (char)ft_get_flag(str[*i], quote_type);
		(*i)++;
	}
	if (str[*i] == c)
		(*i)++;
}

void	ft_flag(char *str, char *s_str)
{
	int	i;

	i = 0;
	if (!str || !s_str)
		return ;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			ft_flag_help(str, s_str, &i);
		else if (str[i] == '#')
			s_str[i++] = HCH;
		else
			i++;
	}
}

void	ft_flag_1(char *str, char *s_str)
{
	int	i;

	i = 0;
	if (!str || !s_str)
		return ;
	while (str[i])
	{
		s_str[i] = ft_get_flag(str[i], 0);
		i++;
	}
}

char	ft_rev_flag_help(int c)
{
	if (c == DQ)
		return ('\"');
	if (c == SQ)
		return ('\'');
	if (c == IN_R)
		return ('<');
	if (c == OUT_R)
		return ('>');
	if (c == HCH)
		return ('#');
	if (c == SPC)
		return (' ');
	if (c == TABS)
		return ('\t');
	return (c);
}
