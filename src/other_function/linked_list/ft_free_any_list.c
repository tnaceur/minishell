/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_any_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:36:12 by abelkhad          #+#    #+#             */
/*   Updated: 2022/12/05 15:37:25 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	ft_free(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
}

void	ft_free_cmds(t_cmd *cmds)
{
	t_cmd	*next;

	if (!cmds)
		return ;
	while (cmds)
	{
		next = cmds->next;
		cmds->i_fd = 0;
		cmds->o_fd = 1;
		free(cmds->cmd_line);
		cmds->cmd_line = NULL;
		ft_free(cmds->cmd_option);
		cmds->cmd_option = NULL;
		ft_free(cmds->files);
		cmds->files = NULL;
		free(cmds->f_error);
		cmds->f_error = NULL;
		free(cmds);
		cmds = next;
	}
}

void	ft_free_env(t_env *env)
{
	t_env	*next;

	if (!env)
		return ;
	while (env)
	{
		next = env->next;
		free(env->variable);
		env->variable = NULL;
		free(env->value);
		env->value = NULL;
		env->i = 0;
		free(env);
		env = next;
	}
}

void	ft_free_file(t_file *file)
{
	int	i;
	int	size;

	if (!file)
		return ;
	i = 0;
	size = file[0].size;
	while (i < size)
	{
		free(file[i].file);
		file[i].file = NULL;
		free(file[i].delimeter);
		file[i].delimeter = NULL;
		if (file[i].fd > 0)
			close(file[i].fd);
		file[i].fd = -10;
		file[i].size = 0;
		file[i].is_used = 0;
		i++;
	}
	free(file);
}

void	ft_free_info(t_info *info)
{
	if (!info)
		ft_put_error("ft_free_info");
	if (info->line)
	{
		ft_free_file(g_glob.file);
		g_glob.file = NULL;
		free(info->line);
		info->line = NULL;
		ft_free_cmds(info->cmds);
		info->cmds = NULL;
	}
}
