/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:37:15 by abelkhad          #+#    #+#             */
/*   Updated: 2022/12/02 00:04:09 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_dup(char *str)
{
	char	*ret;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	ret = (char *)malloc(sizeof(char) * (ft_len(str) + 1));
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
