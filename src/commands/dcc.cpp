#include "../../includes/commands/dcc.hpp"


dcc::dcc()
{
}

dcc::~dcc()
{
}

void	dcc::execute(client *cli, std::vector<client *> *clients, std::vector<std::string> cmd)
{
	for (std::vector<std::string>::iterator it = cmd.begin(); it != cmd.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	(void)cli;
	(void)clients;
}