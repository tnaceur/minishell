/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 00:22:59 by tnaceur           #+#    #+#             */
/*   Updated: 2022/12/05 13:14:24 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_numeric(const char *s)
{
	int	is_numeric;
	int	i;

	is_numeric = 0;
	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] && ft_isdigit(s[i]))
	{
		is_numeric = 1;
		i++;
	}
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] != '\0')
		is_numeric = 0;
	return (is_numeric);
}

static long double	ft_atoi_exit(const char *str)
{
	int			sign;
	long double	nbr;

	sign = 1;
	nbr = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		nbr = (nbr * 10) + (*str - '0');
		str++;
	}
	return (sign * nbr);
}

int	builtin_exit(char **cmd)
{
	long long	exit_status;
	int			size;

	ft_putendl_fd("exit", STDOUT_FILENO);
	size = ft_mlen(cmd);
	if (size == 1)
		exit(g_glob.exit_status);
	exit_status = ft_atoi_exit(cmd[1]);
	if (!is_numeric(cmd[1]) || exit_status > 2147483647
		|| exit_status < -2147483648)
	{
		ft_putstr_fd("MINISHELL: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(255);
	}
	if (size == 3)
	{
		ft_putendl_fd("MINISHELL: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	exit(exit_status);
}
