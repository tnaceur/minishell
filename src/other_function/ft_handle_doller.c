/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_doller.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:36:47 by abelkhad          #+#    #+#             */
/*   Updated: 2022/12/05 14:52:16 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_super_help(char *str, char *src, int *start, int size)
{
	char	*tmp;
	char	*ret;

	if (g_glob.dollar == '$')
	{
		(*start)++;
		ft_super_help2(&tmp, str, start);
	}
	else
		tmp = ft_substr(str, *start, size);
	if (!src || !src[0])
		ret = ft_dup(tmp);
	else
		ret = ft_joind(src, tmp);
	if (g_glob.dollar != '$')
		(*start) = size + (*start);
	free(tmp);
	free(src);
	return (ret);
}

void	ft_super_help2(char **tmp, char *str, int *start)
{
	if (g_glob.in_dquotes == 0 && ft_strchar("\'\"", str[*start]) == 1)
		*tmp = ft_dup("");
	else
	{
		*tmp = ft_get_var(str, start, g_glob.l_env);
		if (g_glob.in_dquotes)
		{
			if (!*tmp)
				*tmp = ft_dup("");
		}
		else
		{
			*tmp = ft_check_exp(*tmp);
			if (*tmp)
				ft_flag_1(*tmp, *tmp);
		}
	}
}

char	*ft_handle_doller(char *str)
{
	int		i;
	int		end;
	char	*ret;

	if (!str)
		return (NULL);
	ret = ft_dup("");
	i = 0;
	while (str[i])
	{
		g_glob.in_dquotes = 0;
		if (str[i] == '\"')
		{
			ft_hdoller_h2(str, &end, i, '\"');
			while (str[i] && i < end)
				ft_hdoller_h(str, &ret, &i);
		}
		else if (str[i] == '\'')
		{
			ft_hdoller_h2(str, &end, i, '\'');
			ret = ft_super_help(str, ret, &i, end - i);
		}
		ft_hdoller_h(str, &ret, &i);
	}
	return (ret);
}

void	ft_hdoller_h(char *str, char **ret, int *i)
{
	if (str[*i] == '$')
	{
		g_glob.dollar = '$';
		*ret = ft_super_help(str, *ret, i, 0);
		g_glob.dollar = '#';
	}
	else if (str[*i])
		*ret = ft_super_help(str, *ret, i, 1);
}

void	ft_hdoller_h2(char *str, int *end, int i, char c)
{
	if (c == '\"')
		g_glob.in_dquotes = 1;
	else
		g_glob.in_dquotes = 0;
	*end = ft_strchar1(str, c, i);
	if ((*end) <= 0)
		*end = i + 1;
}
