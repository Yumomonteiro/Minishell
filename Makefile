NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g #-fsanitize=address

SRCS	= ./main.c \

LIBFT	= libs/libft/libft.a
OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(LIBFT):
	make -C libs/libft

clean:
	$(RM) $(OBJS)
	make clean -C libs/libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C libs/libft

re: fclean all

.PHONY: all clean fclean re
