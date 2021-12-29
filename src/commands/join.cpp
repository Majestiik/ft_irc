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

void	join::execute(std::string buf, client *cli, std::vector<channel *> channels)
{
	int space = buf.find(' ');

	std::string name = buf.substr(0, space);

	if (_checkName(name, channels))
	{
		/*int i = 0;
		while (chan[i].getExists() == true)
			i++;
		chan[i].setName(name);
		chan[i].setExists(true);
		chan[i].addClient(cli);*/
		channels.push_back(new channel(name, cli));
		
	}

	_joinChan(name, cli, channels);
}

void	join::broadcastMsg(std::string buf, client *cli, channel *chan)
{
	std::string message = ":" + cli->getNick() + "!" + cli->getLogin() + "@" + cli->getIp() + " JOIN " + buf + "\r\n";
	send(cli->getSd(), message.c_str(), message.length(), 0);
	std::cout << "listClients : " << chan->listClients() << std::endl;
}

bool	join::_checkName(std::string name, std::vector<channel *> channels)
{
	/*int i = 0;
	while (chan[i].getExists() == true)
	{
		if (chan[i].getName() == name)
			return false;
		i++;
	}
	return true;*/

	for (std::vector<channel *>::iterator it = channels.begin(); it != channels.end(); it++)
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

void	join::_joinChan(std::string name, client *cli, std::vector<channel *> channels)
{
	bool new_cli = false;
	/*int i = 0;
	while (chan[i].getExists() == true)
	{
		if (chan[i].getName() == name)
			break ;
		i++;
	}*/
	channel *chan = _getChan(name, channels);

	if (!_checkClient(cli, chan))
	{
		chan->addClient(cli);
		new_cli = true;
	}
	_informMembers(name, cli, chan);
	if (new_cli)
	{
		//std::cout << GREEN << ""
		std::string tmp = ":server " + std::string(RPL_TOPIC) + " " + cli->getNick() + " " + name + " :Undefined topic\r\n";
		send(cli->getSd(), tmp.c_str(), tmp.length(), 0);
		tmp = ":server " + std::string(RPL_NAMREPLY) + " " + cli->getNick() + " = " + name + " :" + chan->listClients() + "\r\n";
		send(cli->getSd(), tmp.c_str(), tmp.length(), 0);
		tmp = ":server " + std::string(RPL_ENDOFNAMES) + " " + cli->getNick() + " " + name + " : End of NAMES list\r\n";
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
		std::cout << "broadcast to : " << c->getLogin() << std::endl;
		send(c->getSd(), message.c_str(), message.length(), 0);
	}
}

channel*	join::_getChan(std::string name, std::vector<channel *> channels)
{
	for (std::vector<channel *>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		channel *c = *it;
		if (c->getName() == name)
			return c;
	}
	return NULL;
}