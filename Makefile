NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g #-fsanitize=address

SRCS	= ./main.c \
		./srcs/built-in/cd.c \

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
