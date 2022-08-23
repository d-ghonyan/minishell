NAME = minishell
CC = cc
CFLAGS = -c #-Wall -Wextra -Werror
READLINE = -lreadline -L /goinfre/dghonyan/lib/
LIBFT = -lft -L libft
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

%.c:
	$(CC) $(CFLAGS) $(SRCS)

all: lib $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(READLINE) $(LIBFT) -o $(NAME)

lib:
	cd libft && make 

clean:
	rm -f ./*.o libft/*.o

fclean: clean
	rm -f $(NAME) libft/libft.a

re: fclean all

.PHONY: all clean fclean re lib