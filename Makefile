# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/30 10:42:39 by rumachad          #+#    #+#              #
#    Updated: 2024/09/30 11:04:36 by rumachad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror

SRC_PATH = src/
VPATH = $(SRC_PATH)

SRC = main.cpp
OBJS = $(SRC:.cpp=.o)

$(NAME):	$(OBJS)
			$(CXX) -o $(NAME) $(OBJS)

$(OBJS)%.o:	%.c
		$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(NAME)

clean:
		rm $(OBJS)

fclean:	clean
		rm $(NAME)

re:	fclean $(NAME)