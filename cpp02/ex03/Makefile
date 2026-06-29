NAME := bsp
CC := c++
CFLGAS := -Wall -Werror -Wextra -std=c++98 -I.

SRC := main.cpp Fixed.cpp Point.cpp bsp.cpp
OBJ := $(SRC:.cpp=.o)

HEADERS := Fixed.hpp Point.hpp

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $^ -o $@

%.o:%.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
