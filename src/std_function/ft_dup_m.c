/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_m.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:37:11 by abelkhad          #+#    #+#             */
/*   Updated: 2022/12/02 00:05:55 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**ft_dup_m(char **str)
{
	int		i;
	char	**ret;

	if (!str && !*str)
		return (NULL);
	ret = (char **)malloc(sizeof(char *) * (ft_mlen(str) + 1));
	i = -1;
	while (str[++i])
		ret[i] = ft_dup(str[i]);
	ret[i] = NULL;
	return (ret);
}
