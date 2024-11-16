NAME    = minishell
CC      = cc -g
LDLIBS  = -lreadline
CFLAGS  = -Wall -Wextra -Werror -g #-fsanitize=address

SRCS    = main.c \
          $(addprefix srcs/builtins/, cd.c echo.c env.c export.c unset.c pwd.c) \
          $(addprefix srcs/env/, env.c get_env.c sort_env.c shlvl.c env_utils.c) \
          $(addprefix srcs/expansions/, expand.c expand_utils.c) \
					$(addprefix srcs/parse/, parse.c parse_utils.c parse_utils2.c parse_utils3.c) \
					$(addprefix srcs/exec/, bin.c exec.c executable_utils.c pipe.c exec_builtins.c executable_utils2.c executable_utils3.c redir.c) \
					$(addprefix srcs/exit/, exit.c free.c free_utils.c) \
					$(addprefix srcs/mini/, check_type.c fd.c heredoc.c mini_utils.c mini_utils2.c minishell.c) \

OBJS    = $(SRCS:.c=.o)

LIBFT   = libs/libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDLIBS)

$(LIBFT):
	make -C libs/libft -s

clean:
	$(RM) $(OBJS)
	make clean -C libs/libft -s

fclean: clean
	$(RM) $(NAME)
	make fclean -C libs/libft -s

re: fclean all

valgrind: 
	valgrind --trace-children=yes --track-fds=yes --leak-check=full ./$(NAME)

.PHONY: all clean fclean re

.SILENT:
