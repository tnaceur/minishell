/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_of_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:36:32 by abelkhad          #+#    #+#             */
/*   Updated: 2022/12/02 00:08:07 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_env	*ft_create_key_env(char *str, int i)
{
	t_env	*env;
	char	**splited;

	if (!str)
		ft_put_error("str == NULL (ft_create_key_env)");
	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		ft_put_error("malloc (ft_create_key_env)\n");
	splited = ft_split(str, '=');
	if (!splited)
		ft_put_error("splited == NULL (ft_create_key_env)");
	env->variable = splited[0];
	if (env->variable[ft_strlen(env->variable) - 1] == '+')
		env->variable[ft_strlen(env->variable) - 1] = '\0';
	env->value = splited[1];
	if (str[ft_strlen(str) - 1] == '=')
		env->value = ft_calloc(1, 1);
	env->i = i;
	env->is_print = 0;
	env->next = NULL;
	free(splited);
	return (env);
}

t_env	*ft_env_list(char **str)
{
	int		i;
	t_env	*tmp;
	t_env	*ret;

	i = 0;
	if (!str || !*str)
		return (NULL);
	while (str[i])
	{
		if (i == 0)
		{
			ret = ft_create_key_env(str[i], i);
			tmp = ret;
			i++;
		}
		tmp->next = ft_create_key_env(str[i], i);
		tmp = tmp->next;
		i++;
	}
	return (ret);
}
