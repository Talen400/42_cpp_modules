NAME := amateria
CC := c++
CFLAGS := -Wall -Werror -Wextra -std=c++98 -I.

SRC := main.cpp \
	   AMateria.cpp \
	   Character.cpp \
	   Cure.cpp	\
	   Ice.cpp \
	   MateriaSource.cpp \
	   helpers.cpp

OBJ := $(SRC:.cpp=.o)

HEADERS := amateria.h \
	   AMateria.hpp \
	   Character.hpp \
	   Cure.hpp	\
	   Ice.hpp \
	   ICharacter.hpp \
	   IMateriaSource.hpp \
	   MateriaSource.hpp \
	   helpers.h

.SUFFIXES:

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $^ -o $@

%.o:%.cpp $(HEADERS)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

val:
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

.PHONY: all clean fclean re val
