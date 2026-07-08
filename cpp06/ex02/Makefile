NAME := identify

CPP := c++
CFLAGS := -O3 -Wall -Werror -Wextra -std=c++98 -I. \
		  -Wconversion \
		  -Wold-style-cast
LDFLAGS := -g -fsanitize=address

SRC = main.cpp Base.cpp A.cpp B.cpp C.cpp
OBJ := $(SRC:.cpp=.o)
HEADERS := Base.hpp A.hpp B.hpp C.hpp

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
