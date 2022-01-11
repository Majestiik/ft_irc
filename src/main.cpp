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
	/*
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
	serv.start();*/
	return 1;
	
}