NAME := account
CC := c++
INC := -I.
CFLAGS := -Wall -Werror -Wextra -std=c++98 $(INC)

SRC := Account.cpp tests.cpp
OBJ := $(SRC:.cpp=.o)
HEADERS := Account.hpp

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
