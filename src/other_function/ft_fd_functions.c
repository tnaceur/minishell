/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 00:21:06 by abelkhad          #+#    #+#             */
/*   Updated: 2022/12/03 18:49:39 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_close_open_fd(int *fd, int i_fd, int o_fd)
{
	int	i;

	i = 1;
	if (!fd)
		return (-1);
	while (i <= fd[0])
	{
		if (fd[i] != i_fd && fd[i] != o_fd)
			close(fd[i]);
		i++;
	}
	free(fd);
	return (0);
}

void	ft_open_io_help(char *tmp0, int *file, char *type_file)
{
	if (*type_file != '<')
	{
		if (tmp0[0] == '$' && ft_strchar("#%%^=+-,.~;:", tmp0[1]) == 0)
		{
			*type_file = 'g';
			(*file) = -1;
		}
	}
	if (*type_file == 'i')
		(*file) = open(tmp0, O_RDONLY);
	else if (*type_file == '>')
		(*file) = open(tmp0, O_APPEND | O_WRONLY | O_CREAT, 0644);
	else if (*type_file == '<')
		ft_herdoc(g_glob.file, file, *type_file, tmp0);
	else if (*type_file == 'o')
		(*file) = open(tmp0, O_TRUNC | O_WRONLY | O_CREAT, 0644);
}

int	ft_error_open_io(char *tmp0, char type_file, char **error)
{
	char	*tmp;

	tmp = ft_joind(tmp0, " : ");
	if (type_file == 'g')
		*error = ft_joind(tmp, "ambiguous redirect");
	else
		*error = ft_joind(tmp, strerror(errno));
	free(tmp0);
	free(tmp);
	return (0);
}

int	ft_open_io(char *str, int *file, char type_file, char **error)
{
	char	*tmp0;
	char	*tmp;
	int		start;

	start = 1;
	if (str[start] == '>' || str[start] == '<')
		type_file = str[start++];
	while (ft_isspace(str[start]))
		start++;
	if (type_file != '<')
	{
		tmp = ft_dchar_helps(str, "\'\"");
		ft_rev_flag(tmp, tmp);
	}
	else
		tmp = ft_dup(str);
	tmp0 = ft_substr(tmp, start, ft_len(tmp) - start);
	free(tmp);
	ft_open_io_help(tmp0, file, &type_file);
	if (*file == -1)
		return (ft_error_open_io(tmp0, type_file, error));
	free(tmp0);
	return (1);
}

int	ft_open_f_rediration(t_cmd *cmd)
{
	int	i;
	int	*fd;

	if (!cmd->files)
		return (-1);
	i = -1;
	fd = ft_creat_arry_int(ft_mlen(cmd->files));
	while (cmd->files[++i])
	{
		if (cmd->files[i][0] == '<')
		{
			if (!ft_open_io(cmd->files[i], &cmd->i_fd, 'i', &cmd->f_error))
				return (ft_close_open_fd(fd, 0, 1));
			fd[i + 1] = cmd->i_fd;
		}
		else if (cmd->files[i][0] == '>')
		{
			if (!ft_open_io(cmd->files[i], &cmd->o_fd, 'o', &cmd->f_error))
				return (ft_close_open_fd(fd, 0, 1));
			fd[i + 1] = cmd->o_fd;
		}
	}
	return (ft_close_open_fd(fd, cmd->i_fd, cmd->o_fd));
}
