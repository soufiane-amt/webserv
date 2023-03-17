# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samajat <samajat@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/16 17:51:11 by samajat           #+#    #+#              #
#    Updated: 2023/03/17 14:12:44 by samajat          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserver

CC = c++

FLAGS = -Wall -Wextra -Werror


RQS_SRC = requestParser

UTL_SRC = utils




INC = -I ./$(RQS_PATH) -I ./$(UTL_PATH)

INCLUDES =  addprefix(includes/Request/, $(RQS))\
			 addprefix(includes/Utility/, $(UTL))=.hpp

SRC =  addprefix(src/Request/, $(RQS))\
			 addprefix(src/Utility/, $(UTL))


OBJ = $(SRC:=.o)



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

