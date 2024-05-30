NAME	= minishell
CC		= cc -g
LDLIBS = -lreadline
CFLAGS	= -Wall -Wextra -Werror -g #-fsanitize=address

SRCS =  $(wildcard srcs/*.c utils/*.c *.c srcs/env/*.c srcs/builtins/*.c srcs/expansions/*.c  parse/*.c)

LIBFT	= libs/libft/libft.a
OBJS	= $(SRCS:.c=.o)

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