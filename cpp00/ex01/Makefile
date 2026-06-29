NAME := phone
CC := c++
INC := -I.
CFLAGS := -Wextra -Wall -Werror -std=c++98 $(INC)

SRC := main.cpp Contact.cpp PhoneBook.cpp
OBJ := $(SRC:.cpp=.o)
HEADERS := Contact.hpp PhoneBook.hpp

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
