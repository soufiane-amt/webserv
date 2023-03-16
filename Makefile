# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samajat <samajat@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/16 17:51:11 by samajat           #+#    #+#              #
#    Updated: 2023/03/16 18:02:06 by samajat          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserver

CC = c++

FLAGS = -Wall -Wextra -Werror

RQS_PATH = includes/Request/

UTL_PATH = includes/Utility/

INC = -I ./includes

includes = 

FILES = webserv

OBJ = $(SRC:.cpp=.o)



all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re

