/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 23:18:12 by abelkhad          #+#    #+#             */
/*   Updated: 2022/12/05 00:01:18 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_return_value(char *src, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (!src || !tmp)
		return (NULL);
	if (g_glob.here_doc && src[0] == '$')
		return (ft_dup(src));
	if (g_glob.here_doc && src[0] != '$')
		return (ft_joind("$", src));
	if (src[0] == '$')
	{
		if (src[1] == '?')
			return (ft_itoa(g_glob.exit_status));
		if (ft_strchar("\'\"", src[1]) == 1 && !g_glob.in_dquotes)
			return (ft_dup(&src[2]));
		return (ft_dup(src));
	}
	while (tmp)
	{
		if (!ft_strcmp(src, tmp->variable))
			return (ft_return_value2(tmp->value, tmp->variable));
		tmp = tmp->next;
	}
	return (ft_return_value2(NULL, src));
}

char	*ft_return_value2(char *str, char *src)
{
	if (g_glob.not_exp == 1)
		return (ft_check_envv(str, src));
	if (str)
		return (ft_dup(str));
	else
		return (NULL);
}

char	*ft_get_var(char *str, int *start, t_env *env)
{
	int		end;
	int		v;
	char	*tmp;
	char	*ret;

	if (!str)
		return (NULL);
	end = (*start);
	v = 0;
	if (!str[end] || (ft_isalnum(str[end]) == 0 && str[end] != '_'))
	{
		v = 1;
		(*start)--;
		if (str[end] && ft_strchar("\'\"", str[end]) == 0)
			end++;
	}
	ft_get_var_h(str, &end, v);
	if (str[end] && ft_isspace(str[end]) == 0)
		g_glob.not_exp = 0;
	tmp = ft_substr(str, *start, end - (*start));
	ret = ft_return_value(tmp, env);
	if (end > 0)
		(*start) = end;
	free(tmp);
	return (ret);
}

void	ft_get_var_h(char *str, int *end, int v)
{
	while (v == 0 && str[*end])
	{
		if (ft_isalnum(str[*end]) == 0 && str[*end] != '_')
			break ;
		(*end)++;
	}
}

char	*ft_check_envv(char *str, char *envv)
{
	int	i;
	int	valid;

	i = 0;
	valid = 0;
	if (!str || !str[0])
	{
		if (g_glob.not_exp == 1 && g_glob.in_dquotes == 0)
			return (ft_joind("$", envv));
		return (str);
	}
	while (str[i])
	{
		if (ft_isspace(str[i]) == 1)
			valid++;
		i++;
	}
	if (ft_len(str) == valid && g_glob.not_exp == 1 && g_glob.in_dquotes == 0)
		return (ft_joind("$", envv));
	return (ft_dup(str));
}
