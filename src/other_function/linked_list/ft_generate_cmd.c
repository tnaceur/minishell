/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:36:20 by abelkhad          #+#    #+#             */
/*   Updated: 2022/12/05 15:27:36 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_cmd	*ft_create_cmd(char *str)
{
	t_cmd	*cmd;

	if (!str)
		return (NULL);
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->i_fd = STDIN_FILENO;
	cmd->o_fd = STDOUT_FILENO;
	cmd->cmd_line = str;
	cmd->f_error = NULL;
	cmd->cmd_option = NULL;
	cmd->files = NULL;
	cmd->next = NULL;
	ft_handle_cmd(cmd->cmd_line, cmd);
	ft_handle_redirection(cmd->cmd_line, cmd);
	return (cmd);
}

void	ft_list_cmd(t_info *info)
{
	t_cmd	*tmp;
	int		start;
	int		end;

	start = 0;
	end = ft_strchar2(info->line, '|', start);
	if (end <= -1)
		end = ft_len(info->line);
	tmp = ft_create_cmd(ft_substr(info->line, start, end - start));
	info->cmds = tmp;
	while (end < ft_len(info->line))
	{
		start = end + 1;
		end = ft_strchar2(info->line, '|', start);
		if (end <= -1)
			end = ft_len(info->line);
		tmp->next = ft_create_cmd(ft_substr(info->line, start, end - start));
		tmp = tmp->next;
	}
}
