/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joind.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:37:18 by abelkhad          #+#    #+#             */
/*   Updated: 2022/11/06 19:05:30 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_joind(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	ret = (char *)malloc(sizeof(char) * (ft_len(s1) + ft_len(s2) + 1));
	if (!ret)
		return (NULL);
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ret[i + j] = s2[j];
		j++;
	}
	ret[i + j] = '\0';
	return (ret);
}
// char	*ft_joind(char *s1, char *s2)
// {
// 	char	*ret;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;

// 	if (!s1 || !s1[0])
// 		s1 = ft_strdup("");
// 	if (!s2 || !s2[0])
// 		return (NULL);
// 	ret = (char *)malloc(sizeof(char) * (ft_len(s1) + ft_len(s2) + 1));
// 	if (!ret)
// 		return (NULL);
// 	while (s1[i])
// 	{
// 		ret[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[j])
// 	{
// 		ret[i + j] = s2[j];
// 		j++;
// 	}
// 	ret[i + j] = '\0';
// 	// free(s1);
// 	// s1 = NULL;
// 	return (ret);
// }