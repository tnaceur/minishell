/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 08:43:42 by tnaceur           #+#    #+#             */
/*   Updated: 2022/12/04 21:43:59 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_builtin2(t_cmd *vars)
{
	if (!ft_strcmp(vars->cmd_option[0], "pwd"))
	{
		builtin_pwd();
		return (1);
	}
	else if (!ft_strcmp(vars->cmd_option[0], "unset"))
	{
		builtin_unset(vars->cmd_option);
		return (1);
	}
	else if (!ft_strcmp(vars->cmd_option[0], "export"))
	{
		exec_export(vars->cmd_option);
		return (1);
	}
	else if (!ft_strcmp(vars->cmd_option[0], "echo"))
	{
		builtin_echo(vars->cmd_option);
		return (1);
	}
	return (0);
}

int	is_builtin(t_cmd *vars)
{
	if (vars->cmd_option)
	{
		if (!ft_strcmp(vars->cmd_option[0], "exit"))
		{
			builtin_exit(vars->cmd_option);
			return (1);
		}
		else if (!ft_strcmp(vars->cmd_option[0], "cd"))
		{
			exec_cd(vars->cmd_option);
			return (1);
		}
		else if (!ft_strcmp(vars->cmd_option[0], "env"))
		{
			builtin_env(vars->cmd_option);
			return (1);
		}
		else if (is_builtin2(vars))
			return (1);
	}
	return (0);
}

void	exec(t_info *vars)
{
	if (lst_size(vars->cmds) == 1)
		exec_cmd(vars);
	else
		exec_pipe(vars);
}

int	built_here(t_info *vars)
{
	int	fd;

	if (built(vars))
	{
		if (vars->cmds->o_fd > 2)
		{
			fd = dup(1);
			dup2(vars->cmds->o_fd, 1);
		}
		if (is_builtin(vars->cmds))
		{
			if (vars->cmds->o_fd > 2)
			{
				dup2(fd, 1);
				close(vars->cmds->o_fd);
				close(fd);
			}
			return (1);
		}
	}
	return (0);
}

void	exec_cmd(t_info *vars)
{
	int	status;

	if (vars->cmds->i_fd == -1 || vars->cmds->o_fd == -1)
	{
		ft_print_bash_error(vars->cmds->f_error, 0, 1);
		return ;
	}
	if (built_here(vars))
		return ;
	if (vars->cmds->cmd_option && vars->cmds->cmd_option[0])
		ft_cmd_child(vars);
	if (vars->cmds->o_fd > 2)
		close(vars->cmds->o_fd);
	if (vars->cmds->i_fd > 2)
		close(vars->cmds->i_fd);
	g_glob.exit_status = 0;
	wait(&status);
	if (status == 2)
		g_glob.exit_status = 130;
	else if (status == 3)
		g_glob.exit_status = 131;
	else if (WIFEXITED(status))
		g_glob.exit_status = WEXITSTATUS(status);
}
