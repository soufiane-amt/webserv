# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samajat <samajat@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/16 17:51:11 by samajat           #+#    #+#              #
#    Updated: 2023/03/17 14:19:30 by samajat          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserver

CC = clang++

CFLAGS = -Wall -Wextra -Werror

RQS_SRC = requestParser
UTL_SRC = utils

INC = -I ./includes/Request/ -I ./includes/Utility/

INCLUDES = $(addprefix includes/Request/, $(addsuffix .hpp, $(RQS_SRC))) \
		   $(addprefix includes/Utility/, $(addsuffix .hpp, $(UTL_SRC)))

SRC = $(addprefix src/Request/, $(addsuffix .cpp, $(RQS_SRC))) \
	  $(addprefix src/Utility/, $(addsuffix .cpp, $(UTL_SRC)))

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
