NAME = test

SRCS =	test.cpp 

HEADERS =	

OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.cpp=.o))

CC = c++

CFLAGS = -g -Wall -Werror -Wextra -std=c++98 -pedantic

RM = rm -fr

all: $(NAME)

$(NAME):	$(OBJS) $(HEADERS)
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME)
	@echo "\033[0;32mCompilation successful. Executable name: $(NAME)\033[0m"

$(OBJDIR)/%.o: %.cpp $(HEADERS)
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean:		clean
	@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re