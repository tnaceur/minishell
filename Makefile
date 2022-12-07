NAME = minishell

S = built-in/built_norm.c \
	built-in/exec_cd.c \
	built-in/exec_echo.c \
	built-in/exec_env.c \
	built-in/exec_exit.c \
	built-in/exec_export.c \
	built-in/exec_export2.c \
	built-in/exec_pwd.c \
	built-in/exec_unset.c \
	exec/exec.c \
	exec/ft_wait.c \
	exec/pipe.c \
	exec/pipe2.c \
	src/other_function/ft_fd_functions.c \
	src/other_function/ft_flag.c \
	src/other_function/ft_flag2.c \
	src/other_function/ft_generate_layer.c \
	src/other_function/ft_handle_doller.c \
	src/other_function/ft_handle_herdoc.c \
	src/other_function/ft_handle_herdoc2.c \
	src/other_function/ft_handle_string.c \
	src/other_function/ft_list_cmd_option.c \
	src/other_function/ft_put_error.c \
	src/other_function/ft_return_value.c \
	src/other_function/ft_return_value2.c \
	src/other_function/ft_syntax_error.c \
	src/other_function/linked_list/ft_free_any_list.c \
	src/other_function/linked_list/ft_generate_cmd.c \
	src/other_function/linked_list/ft_of_env.c \
	src/std_function/ft_dup.c \
	src/std_function/ft_dup_m.c \
	src/std_function/ft_joind.c \
	src/std_function/ft_len.c \
	src/std_function/ft_split.c \
	src/std_function/ft_split_plus.c \
	src/std_function/ft_strchar.c \
	src/std_function/ft_strstr.c \
	src/std_function/ft_substr.c \
	libft/ft_atoi.c \
	libft/ft_bzero.c \
	libft/ft_calloc.c \
	libft/ft_isalnum.c \
	libft/ft_isalpha.c \
	libft/ft_isdigit.c \
	libft/ft_isspace.c \
	libft/ft_itoa.c \
	libft/ft_putendl_fd.c \
	libft/ft_putstr_fd.c \
	libft/ft_split.c \
	libft/ft_strchr.c \
	libft/ft_strcmp.c \
	libft/ft_strdup.c \
	libft/ft_strjoin.c \
	libft/ft_strlcpy.c \
	libft/ft_strlen.c \
	libft/ft_strncmp.c
	
O = $(S:.c=.o)

C = cc


RL =  -lreadline -L /Users/${USER}/.brew/opt/readline/lib  -I /Users/${USER}/.brew/opt/readline/include

CFLAGS = -Wall -Werror -Wextra

RM = rm -f


all : $(NAME)

$(NAME) : $(O) minishell.c
	$(C) $(CFLAGS) minishell.c  $(O) $(RL) -o $(NAME)
	@echo "=<<<<    compailing done   >>>>="
	@echo "================================\n"
clean :
	$(RM) $(O)
	@echo "=<<<< Deleting '.o' files  >>>>="
	@echo "================================\n"

fclean : clean
	$(RM) $(NAME)
	@echo "=<<<<     Deleting done    >>>>="
	@echo "================================\n"

re : fclean all

.PHONY: all clean fclean re