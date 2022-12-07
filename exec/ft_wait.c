/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 23:21:06 by tnaceur           #+#    #+#             */
/*   Updated: 2022/12/04 23:51:52 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_wait(t_norm *a)
{
	int	i;

	i = 0;
	while (i < a->count + 1)
	{
		waitpid(a->pid[i], &a->status, 0);
		i++;
	}
	if (a->status == 2)
		g_glob.exit_status = 130;
	else if (a->status == 3)
		g_glob.exit_status = 131;
	else if (WIFEXITED(a->status))
		g_glob.exit_status = WEXITSTATUS(a->status);
	free(a->pid);
}
