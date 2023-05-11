# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/16 17:51:11 by samajat           #+#    #+#              #
#    Updated: 2023/05/08 18:23:45 by sismaili         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserver

CC = c++

CFLAGS = -Wall -Wextra -Werror

CFG_SRC = config

UTL_SRC = utils

MAIN =  src/webserv.cpp

INC = -I ./includes/config/ -I ./includes/Utility/

INCLUDES = $(addprefix includes/config/, $(addsuffix .hpp, $(CFG_SRC))) \
		   $(addprefix includes/Utility/, $(addsuffix .hpp, $(UTL_SRC)))

SRC = $(addprefix src/config/, $(addsuffix .cpp, $(CFG_SRC))) \
	  $(addprefix src/Utility/, $(addsuffix .cpp, $(UTL_SRC))) $(MAIN)

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp $(INCLUDES)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
