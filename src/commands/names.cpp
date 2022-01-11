#include "../../includes/commands/names.hpp"

names::names()
{
}
names::~names()
{
}

void names::execute(std::string buf, client *cli, std::vector<channel *> *channels)
{
	std::string message;
	std::string client_list;
	channel *cur_chan;
	size_t i = 1;

	_getCmd(buf);

	if (_cmd.size() > 1)
	{
		while (i < _cmd.size())
		{
			cur_chan = _getChan(_cmd[i], channels);
			if (cur_chan != NULL)
			{
				client_list.append(cur_chan->listClients() + " ");
			}
			i++;
		}
		message = ":server " + std::string(RPL_NAMREPLY) + " " + cli->getNick() + " = " + "server" + " :" + client_list + "\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		message = ":server " + std::string(RPL_ENDOFNAMES) + " " + "server" + " :End of NAMES list\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
	}
}
