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
	std::string message = ":" + cli->getNick() + "!" + cli->getLogin() + "@" + "127.0.0.1" + " JOIN " + buf;
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

void	join::_joinAlreadyExists(std::string name, client *cli, channel *chan)
{
	int i = 0;
	while (chan[i].getExists() == true)
	{
		if (chan[i].getName() == name)
			break ;
		i++;
	}
	chan[i].addClient(cli);
	std::cout << "== " << "i = " << i << " " << chan[i].listClients() << std::endl;
}