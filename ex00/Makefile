GREEN =		\033[0;32m
RED =		\033[0;31m
YELLOW =	\033[0;33m
RESET =		\033[0m

NAME =		btc

SRCS =		main.cpp\
			BitcoinExchange.cpp

HEADERS =	BitcoinExchange.hpp

OBJDIR =	obj
OBJS =		$(addprefix $(OBJDIR)/, $(SRCS:.cpp=.o))

CXX =		c++

CXXFLAGS =	-g -Wall -Werror -Wextra -std=c++98 -pedantic

RM =		rm -fr

all: $(NAME)

$(NAME):		$(OBJS) $(HEADERS)
					@$(CXX) $(OBJS) $(CXXFLAGS) -o $(NAME)
					@echo "$(GREEN)Compilation successful.$(RESET) Executable name: ./$(NAME)"

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
