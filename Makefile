# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/30 10:42:39 by rumachad          #+#    #+#              #
#    Updated: 2024/10/03 13:52:22 by cacarval         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

INCLUDE_PATH = include

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I $(INCLUDE_PATH)

SRC_PATH = src/
VPATH = $(SRC_PATH)

SRC = main.cpp Server.cpp server_Commands.cpp User.cpp

OBJS = $(SRC:.cpp=.o)

$(NAME):	$(OBJS)
	$(CXX) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean $(NAME)