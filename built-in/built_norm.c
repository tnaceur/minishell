/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_norm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 02:07:45 by tnaceur           #+#    #+#             */
/*   Updated: 2022/12/04 23:14:35 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	built(t_info *vars)
{
	if (vars->cmds->cmd_option)
	{
		if (!ft_strcmp(vars->cmds->cmd_option[0], "cd")
			|| !ft_strcmp(vars->cmds->cmd_option[0], "env")
			|| !ft_strcmp(vars->cmds->cmd_option[0], "export")
			|| !ft_strcmp(vars->cmds->cmd_option[0], "unset")
			|| !ft_strcmp(vars->cmds->cmd_option[0], "pwd")
			|| !ft_strcmp(vars->cmds->cmd_option[0], "echo")
			|| !ft_strcmp(vars->cmds->cmd_option[0], "exit"))
			return (1);
	}
	return (0);
}

void	change_pwd(t_env *tmp)
{
	tmp = find_var_env("PWD");
	if (tmp)
	{
		free(tmp->value);
		tmp->value = getcwd(0, PATH_MAX);
	}
}

void	expo_norm(t_env *env, char *str, int a)
{
	int	j;

	if (env->variable[ft_strlen(env->variable) - 1] == '+')
		env->variable[ft_strlen(env->variable) - 1] = '\0';
	if (str[ft_strlen(str) - 1] == '=')
		env->value = ft_calloc(1, 1);
	if (str[a] == '=')
		a++;
	if (str[a])
	{
		j = 0;
		env->value = malloc(ft_strlen(str) - ft_strlen_c(str, '=') + 1);
		while (str[a])
		{
			env->value[j] = str[a];
			a++;
			j++;
		}
		env->value[j] = '\0';
	}
}

t_env	*expo(char *str, int i)
{
	t_env	*env;
	int		a;

	a = 0;
	if (!str)
		ft_put_error("str == NULL (ft_create_key_env)");
	env = (t_env *)malloc(sizeof(t_env));
	env->variable = malloc(ft_strlen_c(str, '=') + 1);
	while (str[a] && str[a] != '=')
	{
		env->variable[a] = str[a];
		a++;
	}
	env->variable[a] = '\0';
	if (!str[a])
		env->value = NULL;
	expo_norm(env, str, a);
	env->i = i;
	env->is_print = 0;
	env->next = NULL;
	return (env);
}

void	the_child_norm(t_cmd **cmd, t_norm *a)
{
	ft_dup_i_o(*cmd, a);
	ft_close_pipe(a);
	if (is_builtin(*cmd))
		exit(g_glob.exit_status);
	while (g_glob.l_env)
	{
		if (!ft_strcmp(g_glob.l_env->variable, "PATH"))
			break ;
		g_glob.l_env = g_glob.l_env->next;
	}
	if (!g_glob.l_env && !ft_strchr((*cmd)->cmd_option[0], '/'))
		error_msg(2, (*cmd)->cmd_option[0]);
	if (g_glob.l_env)
		ft_execute(*cmd, split(g_glob.l_env->value, ':'));
	else
		ft_execute(*cmd, NULL);
}
