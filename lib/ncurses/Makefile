NAME		=	../lib_arcade_ncurses.so

RM		=	rm -f

CC		=	g++

CXXFLAGS	+=	-std=c++11 -Wall -Wextra -Werror -fpic

LDFLAGS		=	-lncurses -shared -rdynamic

SRCS		=	snake_ncurses.cpp	\

OBJS		=	$(SRCS:.cpp=.o)

all		:	$(NAME)

$(NAME)		:	$(OBJS)
			$(CC) -o $(NAME) $(LDFLAGS) $(OBJS)

clean		:
			$(RM) $(OBJS)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
