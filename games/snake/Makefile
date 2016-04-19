##
## Makefile for CPP in /home/delaco_c/rendu/cpp_arcade/lib/openGL
## 
## Made by Delacour Benjamin
## Login   <delaco_c@epitech.net>
## 
## Started on  Tue Mar 29 19:00:32 2016 Delacour Benjamin
## Last update Sat Apr  2 15:01:07 2016 Delacour Benjamin
##

NAME		=	../lib_arcade_snake.so

RM		=	rm -f

CC		=	g++

CXXFLAGS	+=	-std=c++11 -Wall -Wextra -Werror -fpic

LDFLAGS		=	-shared -rdynamic

SRCS		=	Snake.cpp

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
