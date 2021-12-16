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
	if (ac != 3)
	{
		std::cerr << "Argument is missing, please type the port and password" << std::endl;
		std::exit(1);
	}
	if (!checkPort(av[1]))
	{
		std::cerr << "Invalid port, must be digit" << std::endl;
		std::exit(1);
	}
		
	server serv(av);
	serv.start();
	
}