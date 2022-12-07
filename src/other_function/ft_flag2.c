/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:57:10 by abelkhad          #+#    #+#             */
/*   Updated: 2022/12/04 23:50:25 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_rev_flag(char *str, char *s_str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		s_str[i] = ft_rev_flag_help(str[i]);
		i++;
	}
}

char	*ft_dollar_quotes_h(char *tmp, int is_files)
{
	char	*ret;

	if (!tmp)
		return (NULL);
	if (is_files && tmp[0] == '<' && tmp[1] == '<')
		g_glob.here_doc = 1;
	ret = ft_handle_doller(tmp);
	return (ret);
}

void	ft_dollar_quotes(char **str, int is_files)
{
	int		i;
	char	*tmp;
	char	*tmp_1;
	char	*tmp_2;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
	{
		tmp = str[i];
		tmp_1 = ft_dollar_quotes_h(tmp, is_files);
		if (!is_files)
		{
			tmp_2 = ft_dchar_helps(tmp_1, "\'\"");
			ft_rev_flag(tmp_2, tmp_2);
		}
		else
			tmp_2 = ft_dup(tmp_1);
		str[i] = tmp_2;
		free(tmp);
		free(tmp_1);
		g_glob.here_doc = 0;
	}
	g_glob.not_exp = 0;
}
