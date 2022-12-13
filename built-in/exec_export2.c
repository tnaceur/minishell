/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:10:03 by tnaceur           #+#    #+#             */
/*   Updated: 2022/12/13 17:24:31 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	add_exp(int i, char **cmd, t_env *tmp, int *a)
{
	if (!ft_strncmp(cmd[i], tmp->variable, ft_strlen(tmp->variable))
		&& (ft_strlen_c(cmd[i], '=') == (int)ft_strlen(tmp->variable)
			|| ft_strlen_c(cmd[i], '+') == (int)ft_strlen(tmp->variable)))
	{
		*a = 1;
		if (!cmd[i][ft_strlen_c(cmd[i], '+')]
			&& !cmd[i][ft_strlen_c(cmd[i], '=')])
			return (1);
		if (!ft_strchr(cmd[i], '+'))
		{
			free(tmp->value);
			tmp->value = ft_dup(
					cmd[i] + ft_strlen_c(cmd[i], '=') + 1);
		}
		else
			tmp->value = ft_strjoin(tmp->value, cmd[i]
					+ ft_strlen_c(cmd[i], '=') + 1);
		return (1);
	}
	return (0);
}

void	export_arg(t_env *prev, t_env *tmp, char **cmd, int *a)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		*a = 0;
		tmp = g_glob.l_env;
		while (tmp)
		{
			if (!check_exp(cmd[i], a))
				break ;
			if (add_exp(i, cmd, tmp, a))
				break ;
			prev = tmp;
			tmp = tmp->next;
		}
		if (!*a)
		{
			if (!g_glob.l_env)
				g_glob.l_env = expo(cmd[i], 0);
			else
				prev->next = expo(cmd[i], prev->i + 1);
		}
		i++;
	}
}

int	exp_error(char *s, int *a, int i, int print)
{
	int	b;

	b = i;
	while (b >= 0)
	{
		if (s[b] == '=' && b != 0)
			return (0);
		b--;
	}
	if (!s[0] || ft_isdigit(s[0]) || (!ft_isalnum(s[i])
			&& (s[i] != '_' && s[i] != '+' && s[i] != '=')) || s[0] == '=')
	{
		*a = 1;
		g_glob.exit_status = 1;
		if (print)
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(s, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		return (1);
	}
	return (0);
}

void	last_exit(char **s)
{
	int	i;
	int	j;

	i = 1;
	while (s[i])
	{
		j = 0;
		while ((s[i][j] && s[i][j] != '=') || j == 0)
		{
			if (exp_error(s[i], &g_glob.exit_status, j, 0))
				return ;
			if (s[i][j] == '+')
			{
				j++;
				if (!s[i][j] || s[i][j] != '=')
					return ((void)(g_glob.exit_status = 1));
			}
			if (s[i][j] != '=')
				j++;
		}
		i++;
	}
	g_glob.exit_status = 0;
}

void	exec_export(char **cmd)
{
	t_env	*prev;
	t_env	*tmp;
	int		a;

	tmp = g_glob.l_env;
	prev = NULL;
	a = 0;
	if (!cmd[1])
	{
		while (tmp)
		{
			the_smallest();
			tmp = tmp->next;
		}
		tmp = g_glob.l_env;
		while (tmp)
		{
			tmp->is_print = 0;
			tmp = tmp->next;
		}
		g_glob.exit_status = 0;
		return ;
	}
	export_arg(prev, tmp, cmd, &a);
	last_exit(cmd);
}
