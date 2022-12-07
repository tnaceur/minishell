/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:30:18 by tnaceur           #+#    #+#             */
/*   Updated: 2022/12/04 23:49:13 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_close_pipe(t_norm *a)
{
	while (a->start < a->end)
	{
		close(a->fd[a->start][0]);
		close(a->fd[a->start][1]);
		a->start++;
	}
}

void	ft_dup_i_o(t_cmd *cmd, t_norm *a)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (cmd->o_fd == -1 || cmd->i_fd == -1)
		ft_print_bash_error(cmd->f_error, 1, 1);
	if (cmd->i_fd > 2)
	{
		dup2(cmd->i_fd, STDIN_FILENO);
		close(cmd->i_fd);
	}
	if (cmd->o_fd > 2)
	{
		dup2(cmd->o_fd, STDOUT_FILENO);
		close(cmd->o_fd);
	}
	if (!a->i && a->count && cmd->o_fd == 1)
		dup2(a->fd[0][1], STDOUT_FILENO);
	else if (a->i == a->count && a->count && cmd->i_fd == 0)
		dup2(a->fd[a->i - 1][0], 0);
	else
	{
		if (cmd->i_fd == 0 && a->i > 0)
			dup2(a->fd[a->i - 1][0], STDIN_FILENO);
		if (cmd->o_fd == 1 && a->i != a->count)
			dup2(a->fd[a->i][1], STDOUT_FILENO);
	}
}

void	exec_pipe(t_info *vars)
{
	t_norm	a;
	t_cmd	*cmd;

	ft_init_var(vars, &cmd, &a);
	while (cmd)
	{
		if (a.i < a.count)
		{
			pipe(a.fd[a.i]);
			a.end++;
			if (a.i && !(a.i % 2))
			{
				close(a.fd[a.start][0]);
				close(a.fd[a.start][1]);
				a.start++;
			}
		}
		ft_child(&cmd, &a);
	}
	ft_close_pipe(&a);
	ft_wait(&a);
	free(a.fd);
}

void	ft_cmd_child(t_info *vars)
{
	if (fork() == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (vars->cmds->o_fd > 2)
			dup2(vars->cmds->o_fd, 1);
		if (vars->cmds->i_fd > 2)
			dup2(vars->cmds->i_fd, 0);
		if (is_builtin(vars->cmds))
			exit(g_glob.exit_status);
		while (g_glob.l_env)
		{
			if (!ft_strcmp(g_glob.l_env->variable, "PATH"))
				break ;
			g_glob.l_env = g_glob.l_env->next;
		}
		if (!g_glob.l_env && !ft_strchr(vars->cmds->cmd_option[0], '/'))
			error_msg(2, vars->cmds->cmd_option[0]);
		if (!ft_strchr(vars->cmds->cmd_option[0], '/'))
			ft_execute(vars->cmds, split(g_glob.l_env->value, ':'));
		else
			ft_execute(vars->cmds, NULL);
	}
}

int	lst_size(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
