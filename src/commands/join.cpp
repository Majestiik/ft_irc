#include "../../includes/commands/join.hpp"

join::join()
{
}

join::~join()
{
}

void	join::execute(std::string buf, client *cli, std::vector<channel *> *channels)
{
	_getCmd(buf);
	if (_cmd.size() < 2)
	{
		std::string tmp = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cli->getNick() + " " + " :Join :Not enough parameters\r\n";
		send(cli->getSd(), tmp.c_str(), tmp.length(), 0);
		return;
	}

	if (_checkName(_cmd[1], channels))
	{
		channels->push_back(new channel(_cmd[1]));
	}

	_joinChan(_cmd[1], cli, channels);
}

bool	join::_checkName(std::string name, std::vector<channel *> *channels)
{
	for (std::vector<channel *>::iterator it = channels->begin(); it != channels->end(); it++)
	{
		channel *c = *it;
		if (c->getName() == name)
			return false;
	}
	return true;
}

void	join::_joinChan(std::string name, client *cli, std::vector<channel *> *channels)
{
	bool new_cli = false;
	std::string tmp;

	channel *chan = _getChan(name, channels);

	if (chan->isBanned(cli))
	{
		tmp = ":server " + std::string(ERR_BANNEDFROMCHAN) + " " + name + " :Cannot join channel (+b)\r\n";
		send(cli->getSd(), tmp.c_str(), tmp.length(), 0);
		return;
	}
	else if (chan->getInviteOnly() && !cli->isInvited(chan->getName()))
	{
		tmp = ":server " + std::string(ERR_INVITEONLYCHAN) + " " + name + " :Cannot join channel (+i)\r\n";
		send(cli->getSd(), tmp.c_str(), tmp.length(), 0);
		return;
	}
	else if (chan->getLimitNbr() > 0 && chan->getLimitNbr() <= chan->getMembers().size())
	{
		tmp = ":server " + std::string(ERR_CHANNELISFULL) + " " + name + " :Cannot join channel (+l)\r\n";
		send(cli->getSd(), tmp.c_str(), tmp.length(), 0);
		return;
	}
	else if (chan->isMember(cli))
	{
		tmp = ":server " + std::string(ERR_USERONCHANNEL) + " " + cli->getNick() + " " + name + " :is already on channel\r\n";
		send(cli->getSd(), tmp.c_str(), tmp.length(), 0);
		return;
	}
	else if (chan->getPassword() != "" && _cmd[2] != chan->getPassword())
	{
		tmp = ":server " + std::string(ERR_BADCHANNELKEY) + " " + name + " :Cannot join channel (+k)\r\n";
		send(cli->getSd(), tmp.c_str(), tmp.length(), 0);
		return;
	}
	else if (!_checkClient(cli, chan))
	{
		chan->addInvisible(cli);
		chan->addClient(cli);
		if (chan->getMembers().size() == 1)
			chan->addOp(cli);
		new_cli = true;
	}

	_informMembers(name, cli, chan);

	if (new_cli)
	{
		tmp = ":server " + std::string(RPL_TOPIC) + " " + cli->getNick() + " " + name + " :" + chan->getTopic() + "\r\n";
		send(cli->getSd(), tmp.c_str(), tmp.length(), 0);
		tmp = ":server " + std::string(RPL_NAMREPLY) + " " + cli->getNick() + " = " + name + " :" + chan->listClients() + "\r\n";
		send(cli->getSd(), tmp.c_str(), tmp.length(), 0);
		tmp = ":server " + std::string(RPL_ENDOFNAMES) + " " + name + " :End of NAMES list\r\n";
		send(cli->getSd(), tmp.c_str(), tmp.length(), 0);
		
	}
}

void	join::_informMembers(std::string name, client *cli, channel *chan)
{
	std::string message = ":" + cli->getNick() + "!" + cli->getLogin() + "@" + cli->getIp() + " JOIN " + name + "\r\n";
	std::vector<client*> members = chan->getMembers();
	for (std::vector<client*>::iterator it = members.begin(); it != members.end(); it++)
	{
		client *c = *it;
		send(c->getSd(), message.c_str(), message.length(), 0);
	}
}

