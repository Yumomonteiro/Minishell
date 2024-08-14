NAME    = minishell
CC      = cc -g
LDLIBS  = -lreadline
CFLAGS  = -Wall -Wextra -Werror -g #-fsanitize=address

SRCS    = main.c \
          $(addprefix srcs/builtins/, cd.c echo.c env.c export.c unset.c) \
          $(addprefix srcs/env/, env.c get_env.c sort_env.c) \
          $(addprefix srcs/expansions/, expand.c expand_utils.c) \
          $(addprefix srcs/, exec.c exec_utils.c free.c) \
					$(addprefix srcs/parse/, parse.c parse_utils.c parse_utils2.c) \

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

.PHONY: all clean fclean re

.SILENT:
