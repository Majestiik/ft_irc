#include "../../includes/commands/part.hpp"

part::part()
{
}

part::~part()
{
}

void	part::execute(std::string buf, client *cli, std::vector<channel *> *channels)
{
	std::string message;
	_getCmd(buf);

	if (_cmd.size() < 2 || _cmd[1] == ":")
	{
		message = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cli->getNick() + " :Part :Not enough parameters\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
	channel *cur_chan = _getChan(_cmd[1], channels);
	if (cur_chan != NULL && !_checkClient(cli, cur_chan))
	{
		message = ":server " + std::string(ERR_NOTONCHANNEL) + " " + cli->getNick() + " " + cur_chan->getName() + " :You're not on that channel\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
	if (cur_chan != NULL)
	{
		message = ":" + cli->getNick() + "!" + cli->getLogin() + "@" + cli->getIp() + " PART " + _cmd[1] + "\r\n";
		std::vector<client*> members = cur_chan->getMembers();
		for (std::vector<client*>::iterator it = members.begin(); it != members.end(); it++)
		{
			client *c = *it;
			send(c->getSd(), message.c_str(), message.length(), 0);
		}
		cur_chan->deleteEverywhere(cli);
	}
	else
	{
		message = ":server " + std::string(ERR_NOSUCHCHANNEL) + " " + cli->getNick() + " " + _cmd[1] + " :No such channel\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
}
