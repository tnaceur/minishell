/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_plus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:49:18 by abelkhad          #+#    #+#             */
/*   Updated: 2022/12/03 16:50:46 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**ft_split_utmp(char *str, char *tmp, char c)
{
	int		i;
	int		j;
	int		index;
	char	**ret;

	i = 0;
	j = 0;
	if (!str || !tmp)
		return (NULL);
	index = ft_index(tmp, c, i);
	ret = (char **)malloc(sizeof(char *) * (ft_nw(tmp, c) + 1));
	if (!ret)
		return (NULL);
	while (j < ft_nw(tmp, c))
	{
		while (tmp[i] == c)
			i++;
		ret[j] = ft_substr(str, i, index - i + 1);
		i = ++index;
		index = ft_index(tmp, c, i);
		j++;
	}
	ret[j] = NULL;
	return (ret);
}

char	**ft_split_v3(char *str, char *c, int size, char *src)
{
	char	**ret;
	int		i;
	int		j;
	int		end;

	if (!str || !c || size <= 0 || size > ft_len(str))
		return (NULL);
	i = 0;
	j = 0;
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	if (!ret)
		ft_put_error("ret == NULL  (ft_spplite_v3)");
	while (j < size && str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			end = ft_get_next_char(str, c, i);
			ret[j++] = ft_substr(src, i, end - i);
			i = end++;
		}
		else
			i++;
	}
	ret[j] = NULL;
	return (ret);
}
