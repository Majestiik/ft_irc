INCLUDES =	includes/server.hpp\
			includes/parser.hpp\
			includes/client.hpp\
			includes/channel.hpp\
			includes/commands/join.hpp\
			includes/commands/part.hpp

SRCS =	src/server.cpp\
		src/main.cpp\
		src/parser.cpp\
		src/client.cpp\
		src/channel.cpp\
		src/commands/join.cpp\
		src/commands/part.cpp


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
		rm -rf $(OBJS)

fclean : clean
		rm -rf $(NAME)

re :	fclean all