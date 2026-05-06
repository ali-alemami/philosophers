NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lpthread

SRC_FILES = \
	main.c validation.c linked_list.c create_mutexex.c \
	simulation.c philo_cycle1.c philo_cycle2.c utils1.c utils2.c \
	protected_data.c

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