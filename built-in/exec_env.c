/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 00:22:47 by tnaceur           #+#    #+#             */
/*   Updated: 2022/11/28 18:11:00 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_env(char **envp)
{
	t_env	*env;

	env = g_glob.l_env;
	if (envp[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(envp[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_glob.exit_status = 127;
		return (0);
	}
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->variable, env->value);
		env = env->next;
	}
	g_glob.exit_status = 0;
	return (1);
}
