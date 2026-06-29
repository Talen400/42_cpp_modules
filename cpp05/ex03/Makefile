NAME := intern
CPP := c++
CFLAGS := -Wall -Werror -Wextra -std=c++98 -I.

SRC := main.cpp Bureaucrat.cpp AForm.cpp \
	   ShrubberyCreationForm.cpp \
	   PresidentialPardonForm.cpp \
	   RobotomyRequestForm.cpp \
	   Intern.cpp

OBJ := $(SRC:.cpp=.o)
HEADERS := Bureaucrat.hpp AForm.hpp \
	   ShrubberyCreationForm.hpp \
	   PresidentialPardonForm.hpp \
	   RobotomyRequestForm.hpp \
	   Intern.hpp


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
