/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_herdoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:39:43 by abelkhad          #+#    #+#             */
/*   Updated: 2022/12/04 20:44:42 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_hfirst_h(char *str, int *start)
{
	g_glob.here_doc = 1;
	(*start) += 2;
	while (ft_isspace(str[*start]))
		(*start)++;
	if (ft_strchar("<>|;&", str[*start]) == 1 || str[*start] == '\0')
		return (-1);
	return (0);
}

void	ft_herdoc_first(char **str)
{
	int		i;
	int		start;
	char	*tmp;
	t_file	*file;

	if (!str)
		return ;
	file = (t_file *)malloc(sizeof(t_file) * ft_mlen(str));
	ft_create_sfile(str, file, ft_mlen(str));
	i = -1;
	g_glob.file = file;
	while (str[++i] && g_glob.exec)
	{
		start = 0;
		if (file[i].file && file[i].file[0] == '<' && file[i].file[1] == '<')
		{
			if (ft_hfirst_h(file[i].file, &start) == -1)
				return ;
			tmp = ft_substr(file[i].file, start, ft_len(file[i].file) - start);
			file[i].delimeter = ft_handle_doller(tmp);
			free(tmp);
			g_glob.here_doc = 0;
			ft_handle_herdoc(file[i].delimeter, &file[i].fd);
		}
	}
}

void	ft_herdoc(t_file *file, int *fd, char type_file, char *dtr)
{
	int	i;
	int	size;

	if (type_file != '<' || !file || !dtr)
		return ;
	i = 0;
	size = file[0].size;
	while (i < size)
	{
		if (ft_strcmp(dtr, file[i].delimeter) == 0 && file[i].is_used == 0)
		{
			(*fd) = file[i].fd;
			file[i].is_used = 1;
			return ;
		}
		i++;
	}
}

void	ft_hdoc_help(char *str, int *fd, int *file)
{
	char	*tmp_line;
	char	*tmp;

	while (1)
	{
		g_glob.crtl_c = 1;
		tmp_line = readline("> ");
		if (!tmp_line || !ft_strcmp(str, tmp_line))
		{
			free(tmp_line);
			close(fd[1]);
			*file = fd[0];
			return ;
		}
		if (g_glob.dtr)
			tmp = ft_dup(tmp_line);
		else
		{
			tmp = ft_handle_doller(tmp_line);
			ft_rev_flag(tmp, tmp);
		}
		free(tmp_line);
		ft_putendl_fd(tmp, fd[1]);
		free(tmp);
	}
}

void	ft_handle_herdoc(char *str, int *file)
{
	int		fd[2];
	int		s_in;
	char	*tmp1;

	if (!str)
		return ;
	g_glob.here_doc = 1;
	tmp1 = ft_dchar_helps(str, "\'\"");
	g_glob.here_doc = 0;
	if (pipe(fd) == -1)
		ft_put_error("ft_handle_herdoc [open]");
	s_in = dup(0);
	ft_hdoc_help(tmp1, fd, file);
	if (g_glob.std_in == 1)
	{
		g_glob.exec = 0;
		g_glob.std_in = 0;
		dup2(s_in, 0);
	}
	close(s_in);
	g_glob.crtl_c = 0;
	g_glob.dtr = 0;
	free(tmp1);
}
