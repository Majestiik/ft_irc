#include "../../includes/commands/dcc.hpp"


dcc::dcc()
{
}

dcc::~dcc()
{
}

client	*_getClient(std::string name, std::vector<client *> *clients)
{
	client *c;
	for (std::vector<client *>::iterator it = clients->begin(); it != clients->end(); it++)
	{
		c = *it;
		if (name == c->getNick())
			return c;
	}
	return NULL;
}

void	dcc::execute(client *cli, std::vector<client *> *clients, std::vector<std::string> cmd)
{
	for (std::vector<std::string>::iterator it = cmd.begin(); it != cmd.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	(void)cli;
	//if (cmd[3] != "SEND")
	//	return ;
	client *dest = _getClient(cmd[1], clients);
	char delim = 0x01;
	if (cmd[3] == "SEND")
	{
		int sock;
		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		{
			std::cerr << "socket pete dans dcc\n";
			return ;
		}
		sockaddr_in addr;
		int port = std::atoi(cmd[6].c_str());
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr =  INADDR_ANY;//std::atoi(cmd[5].c_str());
		addr.sin_port = htons(port);
		if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		{
			std::cerr << "bind pete dans dcc\n";
			return ;
		}
	}
	std::string message = ":" + cli->getNick() + " PRIVMSG " + dest->getNick() + " :" + delim + " SEND " + cmd[4] + " " + cmd[5] + " " + cmd[6] + " " + cmd[7] + delim + "\r\n";
	//send(dest->getSd(), message.c_str(), message.length(), 0);
	//int sock = socket(AF_INET, SOCK_STREAM, 0);
	//sendfile()
	//std::string message = ""

	


}