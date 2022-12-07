/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_cmd_option.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 01:31:39 by abelkhad          #+#    #+#             */
/*   Updated: 2022/12/05 15:37:10 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_g_glob_check(void)
{
	if (g_glob.here_doc == 1)
	{
		g_glob.dtr = 1;
		g_glob.here_doc = 0;
	}
}

char	*ft_dchar_helps(char *str, char *src)
{
	int		i;
	char	*ret;
	int		size;
	char	c;

	i = 0;
	if (!str)
		return (NULL);
	ret = ft_dup("");
	while (str[i])
	{
		if (ft_strchar(src, str[i]) == 1)
		{
			ft_g_glob_check();
			c = str[i];
			size = ft_size_help(str, &i);
			if (size > 0)
				ret = ft_super_help(str, ret, &i, size);
			if (str[i] == c)
				i++;
		}
		else
			ret = ft_super_help(str, ret, &i, 1);
	}
	return (ret);
}

void	ft_handle_cmd(char *str, t_cmd *cmd)
{
	int		size;
	char	*tmp;
	char	**tmp_1;

	if (!str)
		return ;
	tmp = ft_dup(str);
	ft_r_generate_layer(str, tmp);
	size = ft_nw(tmp, '#');
	tmp_1 = ft_split_utmp(str, tmp, '#');
	free(tmp);
	g_glob.not_exp = 0;
	ft_dollar_quotes(tmp_1, 0);
	cmd->cmd_option = ft_last_check(tmp_1, size);
	ft_free2(tmp_1, size);
}

void	ft_handle_redirection(char *str, t_cmd *cmd)
{
	char	*tmp;
	int		size;

	(void)cmd;
	if (!str)
		return ;
	tmp = ft_dup(str);
	ft_flag(str, tmp);
	ft_generate_layer(tmp, tmp, "< \t>");
	size = ft_count_words(tmp, "< \t>");
	if (size <= 0)
	{
		free(tmp);
		return ;
	}
	cmd->files = ft_split_v3(tmp, "< \t#>", size, str);
	g_glob.not_exp = 1;
	ft_dollar_quotes(cmd->files, 1);
	free(tmp);
	ft_open_f_rediration(cmd);
}
