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
	if (_cmd[3] != "SEND")
		return ;
	//int sock = socket(AF_INET, SOCK_STREAM, 0);
	//sendfile()
	//std::string message = ""


}