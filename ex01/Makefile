NAME := form
CPP := c++
CFLAGS := -Wall -Werror -Wextra -std=c++98 -I.

SRC := main.cpp Bureaucrat.cpp
OBJ := $(SRC:.cpp=.o)
HEADERS := Bureaucrat.hpp

all: $(NAME)

$(NAME): $(OBJ)
	$(CPP) $^ -o $@

%.o:%.cpp $(HEADERS)
	$(CPP) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
