#include "Parsing.hpp"

#include <sstream>
#include <iostream>
#include <vector>

int main() {
	std::vector<std::string> strings;
	std::istringstream f("KICK a b c salut Michel");
	std::string s;
	while (std::getline(f, s, ' ')) {
		strings.push_back(s);
	}
	for(std::vector<std::string>::iterator it = strings.begin(); it != strings.end(); ++it) {
		std::cout << *it << "\n";
	}
}




/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Parsing::Parsing()
{
}

Parsing::Parsing( const Parsing & src )
{
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Parsing::~Parsing()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Parsing &				Parsing::operator=( Parsing const & rhs )
{
	//if ( this != &rhs )
	//{
		//this->_value = rhs.getValue();
	//}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, Parsing const & i )
{
	//o << "Value = " << i.getValue();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/
std::stack<std::string> parse(std::string)
{

}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */