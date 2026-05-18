NAME := shrubbery
CPP := c++
CFLAGS := -Wall -Werror -Wextra -std=c++98 -I.

SRC := main.cpp
OBJ := $(SRC:.cpp=.o)
HEADERS :=

all: $(NAME)

$(NAME): $(OBJ)
	$(CPP) $^ -o $@

%.o:%.cpp $(HEADERS)
	$(CPP) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
