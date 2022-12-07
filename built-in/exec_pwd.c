/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 00:23:10 by tnaceur           #+#    #+#             */
/*   Updated: 2022/12/01 18:46:17 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_pwd(void)
{
	char	cwd[4096];

	getcwd(cwd, 4096);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	g_glob.exit_status = 0;
	return (EXIT_SUCCESS);
}
