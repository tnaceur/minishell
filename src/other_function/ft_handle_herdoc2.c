/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_herdoc2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 21:59:50 by abelkhad          #+#    #+#             */
/*   Updated: 2022/12/04 20:44:19 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_all_files(char *str, int error)
{
	char	*tmp;
	int		size;
	char	**tmp_1;

	if (!str)
		return (error);
	tmp = ft_dup(str);
	ft_flag(str, tmp);
	ft_generate_layer(tmp, tmp, "< \t>");
	size = ft_count_words(tmp, "< \t>");
	if (size <= 0)
	{
		free(tmp);
		return (error);
	}
	tmp_1 = ft_split_v3(tmp, "< \t#>", size, str);
	free(tmp);
	ft_herdoc_first(tmp_1);
	ft_free(tmp_1);
	return (error);
}

void	ft_create_sfile(char **str, t_file *file, int size)
{
	int	i;
	int	end;

	if (!str || !file)
		ft_put_error("create_sfile null");
	i = 0;
	while (str[i])
	{
		end = ft_strchar2(str[i], '|', 0);
		if (end <= -1)
			end = ft_len(str[i]);
		file[i].file = ft_substr(str[i], 0, end);
		file[i].size = size;
		file[i].is_used = 0;
		file[i].delimeter = NULL;
		file[i].fd = -10;
		i++;
	}
}
