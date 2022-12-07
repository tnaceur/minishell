/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 18:35:08 by tnaceur           #+#    #+#             */
/*   Updated: 2022/12/07 15:59:15 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_newline(char *cmd)
{
	int	i;

	if (ft_strncmp(cmd, "-n", 2))
		return (0);
	i = 2;
	while (cmd[i])
	{
		if (cmd[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(char **cmd)
{
	int	newline;
	int	i;

	newline = 1;
	i = 1;
	while (cmd[i] && is_newline(cmd[i]))
	{
		newline = 0;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline)
		printf("\n");
	g_glob.exit_status = 0;
	return (1);
}
