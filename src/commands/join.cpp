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

void	join::execute(std::string buf, client *cli, channel *chan)
{
	std::cout << "buf dans join : " << buf << std::endl;
	std::cout << "cli dans join : " << cli->getLogin() << std::endl;
	int space = buf.find(' ');

	std::string name = buf.substr(0, space);
	std::cout << "name : " << name << std::endl;

	if (_checkName(name, chan))
	{
		int i = 0;
		while (chan[i].getExists() == true)
			i++;
		chan[i].setName(name);
		chan[i].setExists(true);
		chan[i].addClient(cli);
		chan[i].create();
		std::cout << "i a la creation : " << i << std::endl;
	}
	else
	{
		std::cout << "===ALREADY EXIST===\n";
		_joinAlreadyExists(name, cli, chan);
	}


	broadcastMsg(name, cli, chan);
}

void	join::broadcastMsg(std::string buf, client *cli, channel *chan)
{
	std::string message = ":" + cli->getNick() + "!" + cli->getLogin() + "@" + "127.0.0.1" + " JOIN " + buf + "\r\n";
	std::cout << "message : " << message << std::endl;
	send(cli->getSd(), message.c_str(), message.length(), 0);
	std::cout << "listClients : " << chan->listClients() << std::endl;
}

bool	join::_checkName(std::string name, channel *chan)
{
	int i = 0;
	while (chan[i].getExists() == true)
	{
		if (chan[i].getName() == name)
			return false;
		i++;
	}
	return true;
}

bool	join::_checkClient(client *cli, channel *chan, int i)
{
	std::vector<client *> members = chan[i].getMembers();
	client *c;
	for (std::vector<client*>::iterator it = members.begin(); it != members.end(); it++)
	{
		c = *it;
		if (c->getSd() == cli->getSd())
			return true;
	}
	return false;
}

void	join::_joinAlreadyExists(std::string name, client *cli, channel *chan)
{
	int i = 0;
	while (chan[i].getExists() == true)
	{
		if (chan[i].getName() == name)
			break ;
		i++;
	}
	if (!_checkClient(cli, chan, i))
	{
		chan[i].addClient(cli);
		_getOtherMembers(name, cli, chan, i);
		_informOtherMembers(name, cli, chan, i);
		std::cout << "== " << "i = " << i << " " << chan[i].listClients() << std::endl;
	}

}

void	join::_getOtherMembers(std::string name, client *cli, channel *chan, int i)
{
	std::string message;
	std::vector<client*> members = chan[i].getMembers();
	for (std::vector<client*>::iterator it = members.begin(); it != members.end(); it++)
	{
		client *c = *it;
		std::cout << "_getOtherMembers : " << c->getLogin() << std::endl;
		message = ":" + c->getNick() + "!" + c->getLogin() + "@" + "127.0.0.1" + " JOIN " + name + "\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
	}
}

void	join::_informOtherMembers(std::string name, client *cli, channel *chan, int i)
{
	std::string message = ":" + cli->getNick() + "!" + cli->getLogin() + "@" + "127.0.0.1" + " JOIN " + name + "\r\n";
	std::vector<client*> members = chan[i].getMembers();
	for (std::vector<client*>::iterator it = members.begin(); it != members.end(); it++)
	{
		client *c = *it;
		std::cout << "broadcast to : " << c->getLogin() << std::endl;
		send(c->getSd(), message.c_str(), message.length(), 0);
	}
}