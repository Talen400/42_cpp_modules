NAME := converter

CPP := c++
CFLAGS := -O3 -Wall -Werror -Wextra -std=c++98 -I. \
		  -Wstrict-aliasing=3 \
		  -Wconversion \
		  -Wold-style-cast
LDFLAGS := -g -fsanitize=address

SRC = main.cpp ScalarConverter.cpp
OBJ := $(SRC:.cpp=.o)
HEADERS := ScalarConverter.hpp

all: $(NAME)

$(NAME): $(OBJ)
	$(CPP) $(LDFLAGS) $^ -o $@

%.o:%.cpp $(HEADERS)
	$(CPP) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
