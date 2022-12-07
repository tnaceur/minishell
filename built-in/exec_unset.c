/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 00:23:15 by tnaceur           #+#    #+#             */
/*   Updated: 2022/11/27 00:48:28 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	unset_error(char *cmd)
{
	int	valid;
	int	i;

	valid = 0;
	i = 0;
	while (cmd[i])
	{
		if (i == 0 && !ft_isalpha(cmd[i]) && cmd[i] != '_')
			valid = 1;
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			valid = 1;
		i++;
	}
	if (valid || !cmd[0])
	{
		g_glob.exit_status = 1;
		ft_putstr_fd("minishell: unset: '", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (0);
	}
	return (1);
}

int	ft_swap_node(char *s)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = g_glob.l_env;
	while (tmp && ft_strcmp(tmp->variable, s))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp && tmp == g_glob.l_env)
	{
		g_glob.l_env = g_glob.l_env->next;
		free(tmp->variable);
		free(tmp->value);
		free(tmp);
	}
	else
	{
		free(tmp->variable);
		if (tmp->value)
			free(tmp->value);
		prev->next = tmp->next;
		free(tmp);
	}
	return (1);
}

void	builtin_unset(char **cmd)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 1;
	j = 0;
	tmp = g_glob.l_env;
	while (cmd[i])
	{
		tmp = g_glob.l_env;
		while (tmp)
		{
			if (!unset_error(cmd[i]))
			{
				j = 1;
				break ;
			}
			if (!ft_strcmp(cmd[i], tmp->variable) && ft_swap_node(cmd[i]))
				break ;
			tmp = tmp->next;
		}
		i++;
	}
	g_glob.exit_status = j;
}
