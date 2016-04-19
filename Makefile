##
## Makefile for C in /home/delaco_c/rendu/cpp_arcade
## 
## Made by Delacour Benjamin
## Login   <delaco_c@epitech.net>
## 
## Started on  Sat Apr  2 20:18:05 2016 Delacour Benjamin
## Last update Sat Apr  2 20:26:04 2016 Delacour Benjamin
##

NAME		=	arcade

CC		=	g++

RM		=	rm -f

CXXFLAGS	+=	-Wall -Wextra -Werror -std=c++11

LDFLAGS		=	-ldl -pthread

SRCS		=	main.cpp

OBJS		=	$(SRCS:.cpp=.o)

all		:	$(NAME)

$(NAME)		:	$(OBJS)
			$(CC) $(LDFLAGS) $(OBJS) -o $(NAME)

clean		:
			$(RM) $(OBJS)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
