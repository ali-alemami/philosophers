NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_FILES = \
	main.c validation.c tokenization.c linked_list.c execution.c

SRC = $(addprefix src/, $(SRC_FILES))

LIBS_DIR = ./libft
LIBFT = $(LIBS_DIR)/libft.a

HEADERS = -I. -I$(LIBS_DIR)/inc

LDFLAGS = -L$(LIBS_DIR)
LDLIBS = -lft

OBJ = $(SRC:.c=.o)

%.o: %.c
		$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

all : $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(LIBFT):
	make -C $(LIBS_DIR)

clean:
	rm -f $(OBJ)
	make -C $(LIBS_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBS_DIR) fclean

re: fclean all

.PHONY: all clean fclean re