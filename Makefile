# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ffourati <ffourati@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/10 18:41:37 by ffourati          #+#    #+#              #
#    Updated: 2015/01/12 03:02:43 by ffourati         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re warn

CXX := /usr/local/bin/g++ -Wall -Wextra -Werror -std=c++98 -pedantic -O3

SRC_DIR := src
SRC_ := FtRetro.cpp GameEntity.cpp Ship.cpp main.cpp Enemy.cpp
SRC := $(patsubst %.cpp, $(SRC_DIR)/%.cpp, $(SRC_))

OBJ_DIR := obj
OBJ_ := $(SRC_:.cpp=.o)
OBJ := $(patsubst %.o, $(OBJ_DIR)/%.o, $(OBJ_))

INCLUDE_DIR := include

IFLAGS := -I $(INCLUDE_DIR)

BIN_DIR := bin
BIN_ := ft_retro
BIN := $(addprefix $(BIN_DIR)/, $(BIN_))

LFLAGS := -lncurses

all: warn $(OBJ_DIR) $(BIN_DIR) $(BIN)

warn:

$(BIN): $(OBJ)
	$(CXX) -o $@ $(OBJ) $(LFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE_DIR)
	$(CXX) -c -o $@ $(IFLAGS) $(word 1, $^)

$(OBJ_DIR): 
	mkdir -p $@

$(BIN_DIR): 
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(BIN_DIR)

re: fclean all
