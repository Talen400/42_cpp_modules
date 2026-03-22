NAME := harlFilter
CC := c++
INC := -I.
CFLAGS := -Wall -Werror -Wextra -std=c++98 $(INC)

SRC := main.cpp Harl.cpp
OBJ := $(SRC:.cpp=.o)
HEADERS := Harl.hpp

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
