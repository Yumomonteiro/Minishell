NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -lreadline -g -fsanitize=address

SRCS	= ./main.c \
		./srcs/built-in/cd.c \
		./srcs/env/get_env.c \
		./srcs/parse/cmd.c \

LIBFT	= includes/libft/libft.a
OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(LIBFT):
	make -C includes/libft

clean:
	$(RM) $(OBJS)
	make clean -C includes/libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C includes/libft

re: fclean all

.PHONY: all clean fclean re
