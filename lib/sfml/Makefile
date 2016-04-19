##
## Makefile for CPP in /home/delaco_c/rendu/cpp_arcade/lib/openGL
## 
## Made by Delacour Benjamin
## Login   <delaco_c@epitech.net>
## 
## Started on  Tue Mar 29 19:00:32 2016 Delacour Benjamin
## Last update Sun Apr  3 02:46:05 2016 Delacour Benjamin
##

NAME		=	../lib_arcade_sfml.so

RM		=	rm -f

CC		=	g++

CXXFLAGS	+=	-std=c++11 -Wall -Wextra -Werror -fpic

LDFLAGS		=	-lsfml-graphics -lsfml-window -lsfml-system -shared -rdynamic

SRCS		=	MySFML.cpp

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
