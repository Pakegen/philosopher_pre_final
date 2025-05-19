NAME = philosopher

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

SRC =	free.c \
		init.c \
		main.c \
		monitor.c \
		routine.c \
		utils.c \

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -Iinclude

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
