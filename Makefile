# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/04 18:25:41 by bmangin           #+#    #+#              #
#    Updated: 2022/04/05 10:24:56 by bmangin          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME	 = ircserv

override PATH_I		:= includes
override PATH_S		:= srcs
override PATH_B		:= .bin

override VPATH		:= scrs includes

FILES				= server.cpp main.cpp
SRCS				= ${addprefix ${PATH_S}/, ${FILES}}

OBJS				= ${addprefix ${PATH_B}/, ${notdir ${FILES:.cpp=.o}}}

HEADERS				= server.hpp
HEADER				= ${addprefix ${PATH_I}/, ${HEADERS}}

INC		:= -I${PATH_I}

CC		:= c++
FLAG	:= -Wall -Werror -Wextra
CPP_V	:= -std=c++98
CCF		:= ${CC} ${FLAG} ${CPP_V}
RM		:= rm -rf

all:			crea_b ${NAME}

crea_b:
	${shell mkdir -p ${PATH_B}}

${PATH_B}/%.o:	%.cpp ${HEADER}
	${CCF} ${INC} -c $< -o $@

${NAME}:		${OBJS} ${HEADER}
	${CCF} ${OBJS} -o $@

clean:
	${RM} ${PATH_B}

fclean: clean

re: fclean all

.PHONY: all clean fclean re
