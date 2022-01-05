INCLUDES =	includes/server.hpp\
			includes/parser.hpp\
			includes/client.hpp\
			includes/channel.hpp\
			includes/reply_codes.hpp\
			includes/commands/command.hpp\
			includes/commands/invite.hpp\
			includes/commands/join.hpp\
			includes/commands/privmsg.hpp\
			includes/commands/part.hpp\
			includes/commands/mode.hpp\
			includes/commands/quit.hpp

SRCS =	src/server.cpp\
		src/main.cpp\
		src/parser.cpp\
		src/client.cpp\
		src/channel.cpp\
		src/commands/command.cpp\
		src/commands/invite.cpp\
		src/commands/join.cpp\
		src/commands/privmsg.cpp\
		src/commands/part.cpp\
		src/commands/mode.cpp\
		src/commands/quit.cpp


NAME = ircserv

CC = clang++

FLAGS = -Wall -Wextra -Werror #-std=c++98

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