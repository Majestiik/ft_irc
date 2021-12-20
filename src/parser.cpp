#include "../includes/parser.hpp"

parser::parser()
{
}

parser::~parser()
{
}


void	parser::parse(char *buffer, client *cli, channel *channels)
{
	std::string buf = buffer;
	int space = buf.find(' ');
	(void)cli;
	std::cout << "space : " << space << std::endl;
	std::string command = buf.substr(0, space);
	std::cout << "command : " << command << std::endl;

	if (command == "NICK")
	{
		std::cout << "buf.length : " << buf.length() << std::endl;
		cli->setNick(buf.substr(space + 1, buf.length() - (space + 3)));
	}
		
	if (command == "USER")
	{
		buf = buf.substr(space + 1, buf.length() - (space + 3));
		space = buf.find(' ');
		cli->setLogin(buf.substr(0, space));
		space = buf.find(':');
		buf = buf.substr(space + 1, buf.length() - (space + 1));
		cli->setRealName(buf);
	}

	if (command == "JOIN")
	{

		//join j(name, cli, serv);
		buf = buf.substr(space + 1, buf.length() - (space + 3));
		_join.execute(buf, cli, channels);
		
		/*std::cout << "channel name : " << buf << std::endl;
		int i = 0;
		while (channels[i].getExists() == true)
			i++;
		channels[i].setName(buf);
		channels[i].setExists(true);
		channels[i].addClient(cli);
		channels[i].create();

		std::string message = ":" + cli->getNick() + "!" + cli->getLogin() + "@" + "127.0.0.1" + " JOIN " + buf;
		std::cout << "message : " << message << std::endl;
		send(cli->getSd(), message.c_str(), message.length(), 0);*/
	}

	if (command == "EXIT")
		std::exit(0);
}
//(":" + user->getNickName() + "!" + user->getUserName() + "@" + user->getAddress() + " JOIN " + _channelName);

void	parser::setServ(server *serv)
{
	_serv = serv;
}