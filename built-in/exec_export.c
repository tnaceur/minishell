/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:47:08 by tnaceur           #+#    #+#             */
/*   Updated: 2022/12/04 18:30:42 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_export(char *s)
{
	t_env	*tmp;

	tmp = g_glob.l_env;
	while (tmp)
	{
		if (!tmp->is_print && !ft_strcmp(tmp->variable, s))
		{
			tmp->is_print = 1;
			if (!tmp->value)
			{
				printf("declare -x %s\n", tmp->variable);
				break ;
			}
			if (tmp->variable && tmp->value)
				printf("declare -x %s=\"%s\"\n", tmp->variable, tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
}

int	ft_strlen_c(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	*init_s(void)
{
	t_env	*tmp;
	char	*s;

	tmp = g_glob.l_env;
	s = NULL;
	if (!g_glob.l_env->is_print)
		s = g_glob.l_env->variable;
	else
	{
		while (tmp)
		{
			if (!tmp->is_print)
			{
				s = tmp->variable;
				break ;
			}
			tmp = tmp->next;
		}
		tmp = g_glob.l_env;
	}
	return (s);
}

void	the_smallest(void)
{
	t_env	*tmp;
	char	*s;

	tmp = g_glob.l_env;
	s = init_s();
	while (tmp)
	{
		if (!tmp->is_print && ft_strcmp(tmp->variable, s) < 0)
		{
			s = tmp->variable;
			tmp = g_glob.l_env;
		}
		else
			tmp = tmp->next;
	}
	print_export(s);
}

int	check_exp(char *s, int *a)
{
	int	i;

	i = 0;
	if (exp_error(s, a, i, 1))
		return (0);
	while (s[i] && s[i] != '=')
	{
		if (exp_error(s, a, i, 1))
			return (0);
		if (s[i] == '+')
		{
			i++;
			if (!s[i] || s[i] != '=')
			{
				*a = 1;
				ft_putstr_fd("minishell: export: `", 2);
				ft_putstr_fd(s, 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				return (0);
			}
		}
		if (s[i] != '=')
			i++;
	}
	return (1);
}
