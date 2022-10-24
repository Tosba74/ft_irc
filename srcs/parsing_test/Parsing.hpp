#ifndef PARSING_HPP
# define PARSING_HPP

# include <iostream>
# include <string>
# include <stdlib.h>
# include <stack>
class Parsing
{

	public:

		Parsing();
		Parsing( Parsing const & src );
		~Parsing();

		std::stack<std::string> parse(std::string);

		Parsing &		operator=( Parsing const & rhs );

	private:

};

std::ostream &			operator<<( std::ostream & o, Parsing const & i );

#endif /* ********************************************************* PARSING_H */