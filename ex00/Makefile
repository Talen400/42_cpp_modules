NAME := zombie
CC := c++
INC := -I.
CFLAGS := -Wall -Werror -Wextra -std=c++98 $(INC)

SRC := main.cpp newZombie.cpp randomChump.cpp Zombie.cpp
OBJ := $(SRC:.cpp=.o)
HEADERS := Zombie.h Zombie.hpp

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
