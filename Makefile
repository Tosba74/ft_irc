override PATH_I		:= includes/
override PATH_S		:= srcs

NAME := ircserver

IRC:= $(addprefix irc/, Server Client)
SOCKET := $(addprefix socket/, Socket SocketConnection SocketListener SocketServer)

FILES := main.cpp ${addsuffix .cpp, ${IRC}} ${addsuffix .cpp, ${SOCKET}}
SRCS := ${addprefix ${PATH_S}/, ${FILES}}
OBJS := ${SRCS:.cpp=.o}
HEADER := ${addsuffix .hpp, ${IRC}} ${addsuffix .hpp, ${SOCKET}}
HEADER := ${addprefix ${PATH_I}/, ${HEADER}}

INC		:= -I${PATH_I}
CC		:= c++
FLAG	:= -Wall -Werror -Wextra
CPP_V	:= -std=c++98
CCF		:= ${CC} ${FLAG} ${CPP_V} ${INC}
RM		:= rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CCF) -o $(NAME) $(OBJS)

%.o: %.cpp ${HEADER}
	$(CCF) -o $@ -c $<

clean:
	${RM} -f $(OBJS) 

fclean:
	${RM} -f $(NAME) $(OBJS) 

re: fclean all