NAME := brain
CC := c++
CFLAGS := -Wall -Werror -Wextra -std=c++98 -I.

SRC := main.cpp helpers.cpp Animal.cpp Dog.cpp Cat.cpp Brain.cpp

OBJ := $(SRC:.cpp=.o)

HEADERS := helpers.h Animal.hpp Dog.hpp Cat.hpp Brain.hpp

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $^ -o $@

%.o:%.cpp $(HEADERS)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

val: re
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

.PHONY: all clean fclean re val
