CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
NAME = philo

SRCS = main.c utils.c init.c uninit.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -pthread -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
