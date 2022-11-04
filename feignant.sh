#/bin/sh

touch includes/client/command/$1.hpp
touch srcs/client/command/$1.cpp

echo "/* ************************************************************************** */" >> srcs/client/command/$1.cpp
echo "/*                                                                            */" >> srcs/client/command/$1.cpp
echo "/*                                                        :::      ::::::::   */" >> srcs/client/command/$1.cpp
echo "/*   $1.cpp                                           :+:      :+:    :+:   */" >> srcs/client/command/$1.cpp
echo "/*                                                    +:+ +:+         +:+     */" >> srcs/client/command/$1.cpp
echo "/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */" >> srcs/client/command/$1.cpp
echo "/*                                                +#+#+#+#+#+   +#+           */" >> srcs/client/command/$1.cpp
echo "/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */" >> srcs/client/command/$1.cpp
echo "/*   Updated: 2022/11/03 04:32:54 by bmangin          ###   ########lyon.fr   */" >> srcs/client/command/$1.cpp
echo "/*                                                                            */" >> srcs/client/command/$1.cpp
echo "/* ************************************************************************** */" >> srcs/client/command/$1.cpp
echo "" >> srcs/client/command/$1.cpp
echo "#include \"client/command/$1.hpp\"" >> srcs/client/command/$1.cpp
echo "#include \"irc/Server.hpp\"" >> srcs/client/command/$1.cpp
echo "" >> srcs/client/command/$1.cpp
echo "$1::$1(Server *serv): ACommand(serv) {}" >> srcs/client/command/$1.cpp
echo "" >> srcs/client/command/$1.cpp
echo "$1::$1($1 const& src): ACommand(src) {" >> srcs/client/command/$1.cpp
echo "    if (this != &src)" >> srcs/client/command/$1.cpp
echo "        this->_serv = src._serv;" >> srcs/client/command/$1.cpp
echo "}" >> srcs/client/command/$1.cpp
echo "" >> srcs/client/command/$1.cpp
echo "$1::~$1() {}" >> srcs/client/command/$1.cpp
echo "int $1::execute(Client &clicli, std::vector<std::string> args) {}" >> srcs/client/command/$1.cpp
echo "" >> srcs/client/command/$1.cpp
echo "void    $1::descr(Client& clicli) {" >> srcs/client/command/$1.cpp
echo "    clicli << "\e[31mExemple\e[0m\n";" >> srcs/client/command/$1.cpp
echo "}" >> srcs/client/command/$1.cpp

echo "/* ************************************************************************** */" >> includes/client/command/$1.hpp
echo "/*                                                                            */" >> includes/client/command/$1.hpp
echo "/*                                                        :::      ::::::::   */" >> includes/client/command/$1.hpp
echo "/*   $1.hpp                                           :+:      :+:    :+:   */" >> includes/client/command/$1.hpp
echo "/*                                                    +:+ +:+         +:+     */" >> includes/client/command/$1.hpp
echo "/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */" >> includes/client/command/$1.hpp
echo "/*                                                +#+#+#+#+#+   +#+           */" >> includes/client/command/$1.hpp
echo "/*   Created: 2022/05/10 16:27:24 by emenella          #+#    #+#             */" >> includes/client/command/$1.hpp
echo "/*   Updated: 2022/11/01 17:12:51 by bmangin          ###   ########lyon.fr   */" >> includes/client/command/$1.hpp
echo "/*                                                                            */" >> includes/client/command/$1.hpp
echo "/* ************************************************************************** */" >> includes/client/command/$1.hpp
echo "" >> includes/client/command/$1.hpp
echo "#pragma once" >> includes/client/command/$1.hpp
echo "#include \"client/ACommand/$1.hpp\"" >> includes/client/command/$1.hpp
echo "#include \"irc/Channel.hpp\"" >> includes/client/command/$1.hpp
echo "" >> includes/client/command/$1.hpp
echo "class $1 : public ACommand" >> includes/client/command/$1.hpp
echo "{" >> includes/client/command/$1.hpp
echo "    public:" >> includes/client/command/$1.hpp
echo "        $1(Server *serv);" >> includes/client/command/$1.hpp
echo "        $1($1 const& src);" >> includes/client/command/$1.hpp
echo "        ~$1();" >> includes/client/command/$1.hpp
echo "        int     execute(Client &clicli, std::vector<std::string> args);" >> includes/client/command/$1.hpp
echo "		void	descr(Client& clicli);" >> includes/client/command/$1.hpp
echo "};" >> includes/client/command/$1.hpp

echo "YOUPI!"