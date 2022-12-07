/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:36:59 by abelkhad          #+#    #+#             */
/*   Updated: 2022/12/03 18:23:11 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_put_error(char *str)
{
	write(2, "Error \n  ", ft_len("Error \n  "));
	if (str)
	{
		write(2, str, ft_len(str));
		write(2, "\n", 1);
	}
	exit(1);
}

void	ft_print_bash_error(char *str, int i, int n_exit)
{
	write(2, "minishell: ", ft_len("minishell: "));
	if (str)
	{
		write(2, str, ft_len(str));
		write(2, "\n", 1);
	}
	g_glob.exit_status = n_exit;
	if (i)
		exit(n_exit);
}

int	ft_print_syntax_error(int error, char *c)
{
	g_glob.exit_status = 258;
	if (error == -1)
	{
		write(2, "minishell: open ", ft_len("minishell: open "));
		write(2, &c[0], 1);
		write(2, " \n", 2);
	}
	else
	{
		write(2, "minishell: syntax error near ", \
				ft_len("minishell: syntax error near "));
		if (c[0])
		{
			write(2, &c[0], 1);
			if (c[0] == c[1])
				write(2, &c[0], 1);
		}
		else
			write(2, "newline", ft_len("newline"));
		write(2, " \n", 2);
	}
	return (-1);
}
