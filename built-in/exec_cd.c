/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 00:22:18 by tnaceur           #+#    #+#             */
/*   Updated: 2022/12/05 00:54:09 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <sys/stat.h>

t_env	*find_var_env(char *s)
{
	t_env	*tmp;

	tmp = g_glob.l_env;
	while (tmp)
	{
		if (!ft_strcmp(s, tmp->variable))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	cd_err(char **path)
{
	if (path[1][0] == '-' && path[1][1])
	{
		ft_putstr_fd("minishell: cd: -/: invalid option\n"
			"cd: usage: cd [-L|-P] [dir]\n", 2);
		g_glob.exit_status = 1;
		return (1);
	}
	if (!find_var_env("OLDPWD") || !find_var_env("OLDPWD")->value)
	{
		ft_putstr_fd("minihell: cd: OLDPWD not set\n", 2);
		g_glob.exit_status = 1;
		return (1);
	}
	return (0);
}

void	to_old(char **path, t_env *tmp)
{
	char	*new_path;
	char	*s;

	if (cd_err(path))
		return ;
	if (path[1][0] == '-' && !path[1][1])
	{
		tmp = find_var_env("OLDPWD");
		new_path = ft_dup(tmp->value);
		s = getcwd(0, PATH_MAX);
		if (chdir(new_path) == -1)
		{
			free(new_path);
			free(s);
			return (ft_print_bash_error("No such file or directory", 0, 1));
		}
		printf("%s\n", new_path);
		free(tmp->value);
		tmp->value = s;
		free(new_path);
		change_pwd(tmp);
		g_glob.exit_status = 0;
	}
}

void	cd_path(char **path, t_env *tmp, char *home)
{
	char	*s;

	tmp = find_var_env("OLDPWD");
	s = getcwd(0, PATH_MAX);
	if (!path[1])
	{
		if (chdir(home) == -1)
			return (free(s), ft_print_bash_error("cd: HOME not set", 0, 1));
	}
	else if (chdir(path[1]) == -1)
		return (free(s),
			ft_print_bash_error("No such file or directory", 0, 1));
	if (tmp)
	{
		free(tmp->value);
		tmp->value = s;
	}
	else
		free(s);
	change_pwd(tmp);
	g_glob.exit_status = 0;
}

void	exec_cd(char **path)
{
	char		*home;
	t_env		*tmp;

	tmp = NULL;
	if (find_var_env("HOME"))
		home = find_var_env("HOME")->value;
	else
		home = NULL;
	if (!path[1] || path[1][0] != '-')
	{
		if ((!path[1] && home && !home[0])
			|| (path[1] && !path[1][0]))
			return ((void)(g_glob.exit_status = 0));
		cd_path(path, tmp, home);
		return ;
	}
	to_old(path, tmp);
}
