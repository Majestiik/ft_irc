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

	if (_cmd.size() == 2 && _cmd[1] == " ")
		_cmd.pop_back();

	if (_cmd.size() > 1)
	{
		while (i < _cmd.size())
		{
			cur_chan = _getChan(_cmd[i], channels);
			if (cur_chan != NULL)
				_DisplayNames(cur_chan, cli);
			i++;
		}
	}
}

void names::_DisplayNames(channel *chan, client *cli)
{
	std::string message;
	std::string client_list;
	std::vector<client *> members = chan->getMembers();

	if ((chan != NULL && !chan->getPrivate() && !chan->getSecret()) || (chan != NULL && chan->isMember(cli)))
	{
		for (std::vector<client *>::iterator it = members.begin(); it != members.end(); it++)
		{
				client_list.append((*it)->getNick() + " ");
		}
		message = ":server " + std::string(RPL_NAMREPLY) + " " + cli->getNick() + " = " + "-" + chan->getName() + " :" + client_list + "\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		message = ":server " + std::string(RPL_ENDOFNAMES) + " " + "server" + " :End of NAMES list\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
	}	
}
