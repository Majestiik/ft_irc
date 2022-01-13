#include "../includes/server.hpp"

bool	checkPort(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return false;
		str++;
	}
	return true;
}

int main(int ac, char **av)
{
	try
	{
		if (ac != 3)
			throw servException::argument();
		if (!checkPort(av[1]))
			throw servException::non_numeric();
		server serv(av);
		serv.start();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return 1;
	
}