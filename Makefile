# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/30 10:42:39 by rumachad          #+#    #+#              #
#    Updated: 2024/10/17 15:00:35 by rumachad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

INCLUDE_PATH = include

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g -I $(INCLUDE_PATH)

SRC_PATH = src/
VPATH = $(SRC_PATH) $(SRC_PATH)/commands

SRC = main.cpp Server.cpp User.cpp Commands.cpp Join.cpp Channel.cpp \
		Who.cpp Mode.cpp Nick.cpp Quit.cpp PrivMsg.cpp Kick.cpp signals.cpp Topic.cpp

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