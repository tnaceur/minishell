/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:37:32 by abelkhad          #+#    #+#             */
/*   Updated: 2022/12/03 16:56:46 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_len(char *str)
{
	int	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

int	ft_mlen(char **m)
{
	int	i;

	i = 0;
	if (m && *m)
		while (m[i])
			i++;
	return (i);
}

int	*ft_creat_arry_int(int size)
{
	int	*fd;
	int	i;

	fd = (int *)malloc(sizeof(int) * (size + 1));
	if (!fd)
		ft_put_error("fd == NULL (ft_open_f_rediration)");
	i = 0;
	fd[i] = size;
	while (++i <= size)
		fd[i] = -10;
	return (fd);
}

int	ft_count_words(char *str, char *src)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_strchar(src, str[i]) == 1 && (ft_strchar(src, str[i + 1]) != 1
				|| str[i + 1] == 0))
			count++;
		i++;
	}
	return (count);
}
