/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 09:46:14 by tnaceur           #+#    #+#             */
/*   Updated: 2022/12/04 23:47:12 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_path(char **path, char *cmd)
{
	int	i;

	i = 0;
	if (!cmd[0])
		error_msg(1, cmd);
	if (!path)
		error_msg(2, cmd);
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], cmd);
		if (access(path[i], F_OK) == 0)
		{
			return (path[i]);
		}
		i++;
	}
	return (NULL);
}

void	error_msg(int n, char *cmd)
{
	if (n == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	if (n == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(127);
	}
}

void	ft_execute(t_cmd *a, char **path)
{
	char	*cmd_path;

	if (a->cmd_option[0])
	{
		if (!access(a->cmd_option[0], F_OK) && ft_strchr(a->cmd_option[0], '/'))
		{
			if (execve(a->cmd_option[0], a->cmd_option, g_glob.env) == -1)
				perror("minishell");
			exit(126);
		}
		cmd_path = get_path(path, a->cmd_option[0]);
		if (!cmd_path)
			error_msg(1, a->cmd_option[0]);
		free(path);
		if (execve(cmd_path, a->cmd_option, g_glob.env) == -1)
			perror("minishell");
	}
}

void	ft_child(t_cmd **cmd, t_norm *a)
{
	if ((*cmd)->cmd_option && (*cmd)->cmd_option[0])
	{
		a->pid[a->proc++] = fork();
		if (a->pid[a->proc - 1] == 0)
		{
			the_child_norm(cmd, a);
		}
	}
	if ((*cmd)->i_fd != 0)
		close((*cmd)->i_fd);
	if ((*cmd)->o_fd != 1)
		close((*cmd)->o_fd);
	a->i++;
	*cmd = (*cmd)->next;
}

int	ft_init_var(t_info *vars, t_cmd **cmd, t_norm *a)
{
	a->start = 0;
	a->end = 0;
	a->proc = 0;
	a->count = lst_size(vars->cmds) - 1;
	if (!a->count && is_builtin(vars->cmds))
		return (0);
	a->fd = malloc(a->count * sizeof(int *));
	a->pid = malloc((a->count + 1) * sizeof(int));
	a->i = 0;
	*cmd = vars->cmds;
	return (1);
}
