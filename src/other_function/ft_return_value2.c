/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return_value2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 22:47:10 by abelkhad          #+#    #+#             */
/*   Updated: 2022/12/05 15:39:46 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_check_exp(char *str)
{
	int	i;

	if (!str || !str[0])
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) == 0)
			return (str);
		i++;
	}
	free(str);
	return (NULL);
}

int	ft_last_check_h(char **str, int size)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < size)
	{
		if (str[i])
			count++;
		i++;
	}
	return (count);
}

char	**ft_last_check(char **str, int size)
{
	int		i;
	int		j;
	char	**ret;

	i = 0;
	j = ft_last_check_h(str, size);
	ret = (char **)malloc(sizeof(char *) * (j + 1));
	if (!ret)
		ft_put_error("ft_last_check malloc failed");
	j = 0;
	while (i < size)
	{
		if (str[i])
		{
			ret[j] = ft_dup(str[i]);
			j++;
		}
		i++;
	}
	ret[j] = NULL;
	return (ret);
}

void	ft_free2(char **tmp, int size)
{
	int	i;

	if (!tmp)
		return ;
	i = 0;
	while (i < size)
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
	return ;
}
