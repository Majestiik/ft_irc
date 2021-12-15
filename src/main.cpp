#include "../includes/server.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
		std::exit(1);
	server serv(av);
	serv.start();
	
}