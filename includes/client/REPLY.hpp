#pragma once


#define ERR_NEEDMOREPARAMS(command) "461 " + command " :Not enough parameters"
#define ERR_ALREADYREGISTRED "462 :You have already registered"
#define ERR_NONICKNAMEGIVEN "431 :No nickname given"
#define ERR_ERRONEUSNICKNAME "432 :Erroneus nickname"
#define ERR_NICKNAMEINUSE "433 :Nickname is already in use"
#define ERR_NICKCOLLISION(nick, user, host) "436 " + "<nick> :Nickname collision KILL from <user>@<host>"
#define ERR_NOSUCHCHANNEL(channel) "403 " + channel + " :No such channel"