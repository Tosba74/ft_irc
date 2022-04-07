override PATH_I		:= includes
override PATH_S		:= srcs

NAME := ircserver
FILES := main.cpp Server.cpp
SRCS := ${addprefix ${PATH_S}/, ${FILES}}
OBJS := ${SRCS:.cpp=.o}
HEADER := Server.hpp
HEADER := ${addprefix ${PATH_I}/, Server.hpp}

INC		:= -I${PATH_I}
CC		:= c++
FLAG	:= -Wall -Werror -Wextra
CPP_V	:= -std=c++98
CCF		:= ${CC} ${FLAG} ${CPP_V}
RM		:= rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CCF) -o $(NAME) $(OBJS)

%.o: %.cpp ${HEADER}
	$(CCF) -o $@ -c $< ${INC}

clean:
	${RM} -f $(OBJS) 

fclean:
	${RM} -f $(NAME) $(OBJS) 

re: fclean all