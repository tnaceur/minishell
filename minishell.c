/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:57:05 by abelkhad          #+#    #+#             */
/*   Updated: 2022/12/05 12:24:09 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	ft_init_info(t_info *info, char **env)
{
	char	**str;

	str = (char **)malloc(sizeof(char *) * 3);
	if (!str)
		ft_put_error("ft_init_info malloc failed");
	str[0] = ft_dup("unset");
	str[1] = ft_dup("OLDPWD");
	str[2] = NULL;
	g_glob.env = ft_dup_m(env);
	g_glob.l_env = ft_env_list(env);
	builtin_unset(str);
	exec_export(str);
	ft_free(str);
	info->line = NULL;
	info->my_env = NULL;
	info->cmds = NULL;
}

void	sig_handlre(int sig)
{
	(void)sig;
	g_glob.exit_status = 1;
	if (g_glob.crtl_c == 1)
	{
		g_glob.std_in = 1;
		close(0);
		return ;
	}
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	if (g_glob.is_child == 0)
		rl_redisplay();
	else
	{
		g_glob.exit_status = 130;
		g_glob.is_child = 0;
	}
}

void	ft_engine(t_info *info)
{
	if (!info->line)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	if (info->line && info->line[0])
	{
		add_history(info->line);
		if (ft_all_files(info->line, ft_check(info->line)) != -1)
		{
			if (info->line && info->line[0] && g_glob.exec)
			{
				ft_list_cmd(info);
				g_glob.is_child = 1;
				exec(info);
			}
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_info	*info;

	(void)av;
	(void)ac;
	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		ft_put_error("malloc !!! {main}");
	ft_init_info(info, env);
	while (1)
	{
		g_glob.exec = 1;
		signal(SIGINT, &sig_handlre);
		signal(SIGQUIT, SIG_IGN);
		info->line = readline("[ minishell ] :");
		ft_engine(info);
		g_glob.is_child = 0;
		ft_free_info(info);
	}
}
