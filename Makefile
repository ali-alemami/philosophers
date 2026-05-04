NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
LDFLAGS = -lpthread -fsanitize=address

SRC_FILES = \
	main.c validation.c tokenization.c linked_list.c simulation.c \
	connector.c utils.c utils2.c simulation_utils.c create_mutexex.c

SRC = $(addprefix src/, $(SRC_FILES))

HEADERS = -Iinc

OBJ = $(SRC:.c=.o)

%.o: %.c
		$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re