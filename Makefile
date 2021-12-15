INCLUDES =	includes/server.hpp

SRCS =	src/server.cpp\
		src/main.cpp

NAME = ircserv

CC = clang++

FLAGS = -Wall -Wextra -Werror -std=c++98

OBJS = $(SRCS:.cpp=.o)

.cpp.o:
		$(CC) -g3 $(FLAGS) -c $< -o $(<:.cpp=.o)

$(NAME):	$(OBJS) $(INCLUDES)
			$(CC) -o $(NAME) $(SRCS)

all :	$(NAME)

clean :
		rm -rf $(OBJS) $(OBJS_STL)

fclean : clean
		rm -rf $(NAME) $(NAME_STL)

re :	fclean all