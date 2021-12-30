#include "../../includes/commands/join.hpp"


//join::join(std::string name, client *cli, server *serv): _name(name), _cli(cli), _serv(serv)
//{
//}

join::join()
{
}

join::~join()
{
}

void	join::execute(std::string buf, client *cli, std::vector<channel *> *channels)
{
	if (buf == "#")
	{
		std::string tmp = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cli->getNick() + " " + " :Join :Not enough parameters\r\n";
		send(cli->getSd(), tmp.c_str(), tmp.length(), 0);
		return;
	}

	int space = buf.find(' ');
	std::string name = buf.substr(0, space);

	if (_checkName(name, channels))
	{
		channels->push_back(new channel(name));
	}

	_joinChan(name, cli, channels);
}

void	join::broadcastMsg(std::string buf, client *cli, channel *chan)
{
	std::string message = ":" + cli->getNick() + "!" + cli->getLogin() + "@" + cli->getIp() + " JOIN " + buf + "\r\n";
	send(cli->getSd(), message.c_str(), message.length(), 0);
	std::cout << "listClients : " << chan->listClients() << std::endl;
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

bool	join::_checkClient(client *cli, channel *chan)
{
	std::vector<client *> members = chan->getMembers();
	client *c;
	for (std::vector<client*>::iterator it = members.begin(); it != members.end(); it++)
	{
		c = *it;
		if (c->getSd() == cli->getSd())
			return true;
	}
	return false;
}

void	join::_joinChan(std::string name, client *cli, std::vector<channel *> *channels)
{
	bool new_cli = false;
	std::string tmp;

	channel *chan = _getChan(name, channels);

	if (!_checkClient(cli, chan))
	{
		chan->addClient(cli);
		new_cli = true;
	}
	else
	{
		tmp = ":server " + std::string(ERR_USERONCHANNEL) + " " + cli->getNick() + " " + name + " :is already on channel\r\n";
		send(cli->getSd(), tmp.c_str(), tmp.length(), 0);
		return;
	}

	_informMembers(name, cli, chan);

	if (new_cli)
	{
		tmp = ":server " + std::string(RPL_TOPIC) + " " + cli->getNick() + " " + name + " :Undefined topic\r\n";
		send(cli->getSd(), tmp.c_str(), tmp.length(), 0);
		tmp = ":server " + std::string(RPL_NAMREPLY) + " " + cli->getNick() + " = " + name + " :" + chan->listClients() + "\r\n";
		send(cli->getSd(), tmp.c_str(), tmp.length(), 0);
		tmp = ":server " + std::string(RPL_ENDOFNAMES) + " " + cli->getNick() + " " + name + " : End of NAMES list\r\n";
		send(cli->getSd(), tmp.c_str(), tmp.length(), 0);
	}
	//std::cout << "=-=-=-=-=-chan list clients : " << chan->listClients() << std::endl ;
}

void	join::_informMembers(std::string name, client *cli, channel *chan)
{
	std::string message = ":" + cli->getNick() + "!" + cli->getLogin() + "@" + cli->getIp() + " JOIN " + name + "\r\n";
	std::vector<client*> members = chan->getMembers();
	for (std::vector<client*>::iterator it = members.begin(); it != members.end(); it++)
	{
		client *c = *it;
		std::cout << "broadcast to : " << c->getLogin() << std::endl;
		send(c->getSd(), message.c_str(), message.length(), 0);
	}
}

channel*	join::_getChan(std::string name, std::vector<channel *> *channels)
{
	for (std::vector<channel *>::iterator it = channels->begin(); it != channels->end(); it++)
	{
		channel *c = *it;
		if (c->getName() == name)
			return c;
	}
	return NULL;
}