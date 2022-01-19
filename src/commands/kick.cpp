#include "../../includes/commands/kick.hpp"

kick::kick()
{
}

kick::~kick()
{
}

bool	kick::_checkClientStr(std::string cli, channel *chan)
{
	std::vector<client *> members = chan->getMembers();
	client *c;
	for (std::vector<client*>::iterator it = members.begin(); it != members.end(); it++)
	{
		c = *it;
		if (c->getNick() == cli)
			return true;
	}
	return false;
}

void	kick::_informMembers(std::string message, channel *chan)
{
	client *c;
	std::vector<client*> members = chan->getMembers();
	for (std::vector<client*>::iterator it = members.begin(); it != members.end(); it++)
	{
		c = *it;
		send(c->getSd(), message.c_str(), message.length(), 0);
	}
}

client*	kick::_getClient(std::string name, channel *chan)
{
	client *c;
	std::vector<client*> members = chan->getMembers();
	for (std::vector<client*>::iterator it = members.begin(); it != members.end(); it++)
	{
		c = *it;
		if (c->getNick() == name)
			return c;
	}
	return NULL;
}

void	kick::execute(std::string buf, client *cli, std::vector<channel *> *channels)
{
	_getCmd(buf);
	std::string message;
	channel *chan = _getChan(_cmd[1], channels);

	if (chan == NULL)
	{
		message = ":server " + std::string(ERR_NOSUCHCHANNEL) + " " + _cmd[1] + ": No such channel\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return ;
	}
	if (_cmd[2].empty())
	{
		message = ":server " + std::string(ERR_NEEDMOREPARAMS) + " kick: Not enough parameters\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return ;
	}
	if (!_checkClient(cli, chan))
	{
		message = ":server " + std::string(ERR_NOTONCHANNEL) + " " + _cmd[1] + ": You're not on that channel\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return ;
	}
	if (!chan->isOp(cli))
	{
		message = ":server " + std::string(ERR_CHANOPRIVSNEEDED) + " kick: You're not channel operator\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return ;
	}
	if (!_checkClientStr(_cmd[2], chan))
	{
		message = ":server " + std::string(ERR_USERNOTINCHANNEL) + " " + _cmd[2] + " " + _cmd[1] + ": They aren't on that channel\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return ;
	}

	std::string reason;
	if (_cmd.size() > 3)
	{
		size_t i = 3;
		while (i < _cmd.size())
		{
			reason += _cmd[i] + " ";
			i++;
		}
		reason.pop_back();
	}
	std::cout << "reason : " << reason << std::endl;
	if (reason.size() >= 1 && reason[0] != ':')
		reason = ':' + reason;
	message = ":" + cli->getNick() + " KICK " + _cmd[1] + " " + _cmd[2] + " " + reason + "\r\n";
	_informMembers(message, chan);
	chan->deleteEverywhere(_getClient(_cmd[2], chan));
}