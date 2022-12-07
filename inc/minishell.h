/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 01:06:30 by abelkhad          #+#    #+#             */
/*   Updated: 2022/12/05 15:36:38 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define DQ -1
# define SQ -2
# define IN_R -3
# define OUT_R -4
# define HCH -5
# define SPC -6
# define TABS -7

typedef struct s_cmd
{
	int				i_fd;
	int				o_fd;
	char			*cmd_line;
	char			*f_error;
	char			**cmd_option;
	char			**files;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	char			*variable;
	char			*value;
	int				i;
	int				is_print;
	struct s_env	*next;
}					t_env;

typedef struct s_info
{
	char			*line;
	t_env			*my_env;
	t_cmd			*cmds;
}					t_info;

typedef struct s_file
{
	int				fd;
	int				size;
	int				is_used;
	char			*file;
	char			*delimeter;
}					t_file;

typedef struct s_glob
{
	char			dollar;
	int				crtl_c;
	int				exec;
	int				not_exp;
	int				std_in;
	int				here_doc;
	int				dtr;
	int				in_dquotes;
	int				exit_status;
	int				is_child;
	char			**env;
	t_file			*file;
	t_env			*l_env;
}					t_glob;
t_glob				g_glob;

typedef struct s_norm
{
	int				count;
	int				(*fd)[2];
	int				i;
	int				status;
	int				start;
	int				end;
	int				proc;
	int				*pid;
}					t_norm;

int					builtin_env(char **envp);
int					ft_strlen_c(char *s, char c);
int					builtin_pwd(void);
int					builtin_exit(char **cmd);
int					builtin_echo(char **cmd);
int					check_exp(char *s, int *a);
int					lst_size(t_cmd *cmd);
int					ft_init_var(t_info *vars, t_cmd **cmd, t_norm *a);
int					is_builtin(t_cmd *vars);
int					exp_error(char *s, int *a, int i, int print);
int					built(t_info *vars);

void				error_msg(int n, char *cmd);
void				exec_cd(char **path);
void				the_smallest(void);
void				ft_print_bash_error(char *str, int i, int exit);
void				builtin_unset(char **cmd);
void				exec(t_info *vars);
void				exec_pipe(t_info *vars);
void				exec_export(char **cmd);
void				ft_child(t_cmd **cmd, t_norm *a);
void				ft_execute(t_cmd *a, char **path);
void				ft_close_pipe(t_norm *a);
void				exec_cmd(t_info *vars);
void				ft_dup_i_o(t_cmd *cmd, t_norm *a);
void				ft_cmd_child(t_info *vars);
void				change_pwd(t_env *tmp);

t_env				*find_var_env(char *s);
t_env				*expo(char *str, int i);

int					ft_len(char *str);
int					ft_mlen(char **m);
char				*ft_joind(char *s1, char *s2);
char				**ft_split(char *str, char c);
char				**ft_split_utmp(char *str, char *tmp, char c);
char				*ft_substr(char *str, int start, int len);
char				*ft_dup(char *str);
char				**ft_dup_m(char **str);
int					ft_strstr(char *src, char *str);
int					ft_strchar1(char *src, char c, int i);
int					ft_strchar(char *str, char c);
int					is_builtin(t_cmd *vars);
int					ft_nw(char *ss, char cc);
int					ft_index(char *sr, char ch, int i);
int					ft_strstr_v2(char *str, char *src, int i);
char				**ft_split_v3(char *str, char *c, int size, char *src);
void				error_msg(int n, char *cmd);
int					ft_get_next_char(char *str, char *c, int start);
char				*ft_handle_doller(char *str);

void				ft_put_error(char *str);
void				exec_cd(char **path);
int					builtin_env(char **envp);
int					builtin_pwd(void);
int					builtin_exit(char **cmd);
int					builtin_echo(char **cmd);
void				ft_print_bash_error(char *str, int i, int n_exit);
void				ft_str(void);

t_env				*ft_env_list(char **str);
t_env				*ft_create_key_env(char *str, int i);

t_cmd				*ft_create_cmd(char *str);
void				ft_print_cmd(t_cmd *cmd);
void				ft_list_cmd(t_info *info);
void				ft_handle_redirection(char *str, t_cmd *cmd);
void				exec(t_info *vars);
void				exec_pipe(t_info *vars);

char				*ft_get_str_cmd(t_info *info, char c, int start);
int					ft_nbr_of_char(char *str, char c);
void				ft_generate_layer(char *str, char *s_str, char *c);
void				ft_r_generate_layer(char *str, char *s_str);

void				ft_free(char **s);
void				ft_free_env(t_env *env);
void				ft_free_info(t_info *info);
void				ft_free_cmds(t_cmd *cmds);
int					ft_close_open_fd(int *fd, int i_fd, int o_fd);
int					ft_open_f_rediration(t_cmd *cmd);
void				exec_export(char **cmd);
int					ft_nbr_of_char(char *str, char c);
int					lst_size(t_cmd *cmd);
void				exec_cmd(t_info *vars);
int					ft_strchar2(char *src, char c, int start);
int					ft_check(char *str);
int					ft_strchar2(char *src, char c, int start);
char				*ft_super_help(char *str, char *src, int *start, int size);
char				*ft_dchar_helps(char *str, char *src);
void				ft_handle_herdoc(char *str, int *file);
void				the_child_norm(t_cmd **cmd, t_norm *a);

int					ft_size_help(char *str, int *i);
int					ft_last_check_h(char **str, int size);

void				ft_handle_cmd(char *str, t_cmd *cmd);
void				ft_wait(t_norm *a);
void				ft_flag(char *str, char *s_str);
char				*ft_check_envv(char *str, char *envv);
int					ft_get_flag(char c, int type_quote);
void				ft_flag_1(char *str, char *s_str);
void				ft_rev_flag(char *str, char *s_str);
char				ft_rev_flag_help(int c);
void				ft_dollar_quotes(char **str, int is_file);
int					ft_count_words(char *str, char *src);
void				ft_herdoc(t_file *file, int *fd, char type_file, char *dtr);
void				ft_herdoc_first(char **str);
void				ft_create_sfile(char **str, t_file *file, int size);
int					ft_all_files(char *str, int error);
void				sig_handlre(int sig);
int					*ft_creat_arry_int(int size);
int					ft_check_h2(char *str, int *i);
int					ft_check_h3(char *str, int *i, int swt);
int					ft_check_engine(char *str, int *i);
int					ft_print_syntax_error(int error, char *c);

void				ft_hdoller_h(char *str, char **ret, int *i);
void				ft_hdoller_h2(char *str, int *end, int i, char c);
char				*ft_return_value2(char *str, char *src);
void				ft_super_help2(char **tmp, char *str, int *start);
char				*ft_get_var(char *str, int *start, t_env *env);
void				ft_get_var_h(char *str, int *end, int v);

char				*ft_check_exp(char *str);
char				**ft_last_check(char **str, int size);

void				ft_free2(char **tmp, int size);
#endif