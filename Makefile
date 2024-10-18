# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/30 10:42:39 by rumachad          #+#    #+#              #
#    Updated: 2024/10/18 13:28:13 by jmarinho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ---------------------------------- COLORS ------------------------------------

RED = \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[1;35m
RESET = \033[0m
NAME = ircserv

# --------------------------------- VARIABLES ----------------------------------

INCLUDE_PATH = include

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g -I $(INCLUDE_PATH)

SRC_PATH = src/
VPATH = $(SRC_PATH) $(SRC_PATH)/commands

SRC = main.cpp Server.cpp User.cpp Commands.cpp Join.cpp Channel.cpp \
		Who.cpp Mode.cpp Nick.cpp Quit.cpp PrivMsg.cpp Kick.cpp signals.cpp Topic.cpp

OBJ_PATH = obj/
OBJ_FILES = $(SRC:.cpp=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

# ----------------------------------- RULES ------------------------------------

$(NAME):	$(OBJS)
	@$(CXX) -o $(NAME) $(OBJS)
	@echo "$(GREEN)	<TresPingados> IRC_SERVER READY TO LAUNCH $(RESET)"

$(OBJ_PATH)%.o: %.cpp
	@mkdir -p $(OBJ_PATH)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(NAME)

clean:
	@rm -f $(OBJS)
	@echo "$(RED)	Object files were removed.$(RESET)"

fclean:	clean
	@rm -f $(NAME)
	@echo "$(RED)	Executable ./$(NAME) was removed.\n$(RESET)"

re:	fclean $(NAME)
	