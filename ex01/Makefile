NAME =		RPN

SRCS =		main.cpp\
			RPN.cpp

HEADERS =	RPN.hpp

OBJDIR =	obj
OBJS =		$(addprefix $(OBJDIR)/, $(SRCS:.cpp=.o))

CXX =		c++

CXXFLAGS =	-g -Wall -Werror -Wextra -std=c++98 -pedantic

RM =		rm -fr

all: $(NAME)

$(NAME):		$(OBJS) $(HEADERS)
					@$(CXX) $(OBJS) $(CXXFLAGS) -o $(NAME)
					@echo "\033[0;32mCompilation successful. \033[0;37m Executable name: ./$(NAME)\033[0m"

$(OBJDIR)/%.o:	%.cpp $(HEADERS)
					@mkdir -p $(OBJDIR)
					@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
					@$(RM) $(OBJS)
					@$(RM) $(OBJDIR)

fclean:			clean
					@$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
