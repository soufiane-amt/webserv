# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/16 17:51:11 by samajat           #+#    #+#              #
#    Updated: 2023/06/14 17:24:10 by fech-cha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

RQS_SRC =  errorManager requestParser

CFG_SRC = config

RSP_SRC = responding

CGI_SRC = cgiProgram

SERVER_SRC = appendClientSide pollingServ tcpServer

UTL_SRC = utils exception

MAIN =  srcs/webserv.cpp

INC = -I ./includes/Request/ -I ./includes/Response/ -I ./includes/Utility/ -I ./includes/config/ -I ./includes/cgi_inc -I ./includes/src_inc/

INCLUDES = $(addprefix includes/Request/, $(addsuffix .hpp, $(RQS_SRC))) \
		   $(addprefix includes/Response/, $(addsuffix .hpp, $(RSP_SRC)))\
		   $(addprefix includes/Utility/, $(addsuffix .hpp, $(UTL_SRC))) \
		   $(addprefix includes/config/, $(addsuffix .hpp, $(CFG_SRC))) \
		   $(addprefix includes/cgi_inc/, $(addsuffix .hpp, $(CGI_SRC))) \
		   $(addprefix includes/src_inc/, $(addsuffix .hpp, $(SERVER_SRC))) 
		

SRC = $(addprefix srcs/Request/, $(addsuffix .cpp, $(RQS_SRC))) \
		$(addprefix srcs/Config/, $(addsuffix .cpp, $(CFG_SRC))) \
		$(addprefix srcs/Response/, $(addsuffix .cpp, $(RSP_SRC))) \
		$(addprefix srcs/socketServer/, $(addsuffix .cpp, $(SERVER_SRC))) \
		$(addprefix srcs/cgi/, $(addsuffix .cpp, $(CGI_SRC))) \
	  	$(addprefix srcs/Utility/, $(addsuffix .cpp, $(UTL_SRC))) $(MAIN)

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
