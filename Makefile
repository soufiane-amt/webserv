# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samajat <samajat@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/16 17:51:11 by samajat           #+#    #+#              #
#    Updated: 2023/03/23 17:43:40 by samajat          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

RQS_SRC = requestParser errorManager

RSP_SRC = responding

UTL_SRC = utils exception

MAIN =  src/webserv.cpp

INC = -I ./includes/Request/ -I ./includes/Response/ -I ./includes/Utility/

INCLUDES = $(addprefix includes/Request/, $(addsuffix .hpp, $(RQS_SRC))) \
		   $(addprefix includes/Response/, $(addsuffix .hpp, $(RSP_SRC)))\
		   $(addprefix includes/Utility/, $(addsuffix .hpp, $(UTL_SRC))) \

SRC = $(addprefix src/Request/, $(addsuffix .cpp, $(RQS_SRC))) \
	  $(addprefix src/Response/, $(addsuffix .cpp, $(RSP_SRC))) \
	  $(addprefix src/Utility/, $(addsuffix .cpp, $(UTL_SRC))) $(MAIN)

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -g

%.o: %.cpp $(INCLUDES)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@ -g

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
