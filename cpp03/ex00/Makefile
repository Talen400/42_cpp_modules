NAME := clap
CC := c++
CFLAGS := -Wall -Werror -Wextra -std=c++98 -I.

SRC := main.cpp ClapTrap.cpp
OBJ := $(SRC:.cpp=.o)

HEADERS := ClapTrap.hpp

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $^ -o $@

%.o:%.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
