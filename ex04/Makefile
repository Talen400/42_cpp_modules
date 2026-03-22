NAME := sed_is_for_losers
CC := c++
INC := -I.
CFLAGS := -Wall -Werror -Wextra -std=c++98 $(INC)

SRC := main.cpp
OBJ := $(SRC:.cpp=.o)
HEADERS :=

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f *.replace

re: fclean all
