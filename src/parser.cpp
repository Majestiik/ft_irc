#include "../includes/parser.hpp"

parser::parser()
{
}

parser::~parser()
{
}


void	parser::parse(std::string buf, client *cli, std::vector<channel *> channels)
{
	int space = buf.find(' ');
	(void)cli;
	std::string command = buf.substr(0, space);
	
	if (command == "NICK")
	{
		buf = buf.substr(space + 1, buf.length() - space - 1);
		space = buf.find('U');
		if (space > 0)
		{
			cli->setNick(buf.substr(0, space - 1));
			buf = buf.substr(space, buf.length() - space);
			command = "USER";
			space = buf.find(' ');
		}
		else
			cli->setNick(buf.substr(0, buf.length() - 2));
	}
		
	if (command == "USER")
	{
		buf = buf.substr(space + 1, buf.length() - (space + 3));
		space = buf.find(' ');
		cli->setLogin(buf.substr(0, space));
		space = buf.find(':');
		if (space < 0)
			space = buf.find('*') + 1;
		buf = buf.substr(space + 1, buf.length() - (space + 1));
		cli->setRealName(buf);
		std::string message = ":" + cli->getIp() + " 001 " + cli->getNick() + " :Welcome to the IRMEGASTONKS network, you'll see it's incredible\r\n";
		if (send(cli->getSd(), message.c_str(), message.length(), 0) != (long)message.length())
			std::cerr << "send" << std::endl;
		else
			std::cout << "Welcome message sent successfully" << std::endl;
	}

	if (command == "JOIN")
	{
		buf = buf.substr(space + 1, buf.length() - (space + 3));
		_join.execute(buf, cli, channels);
	}

	if (command == "PRIVMSG")
	{
		std::cout << "PRIVMSG COMMAND DETECTED" << std::endl;
		_privmsg.execute(buf, cli, channels, _serv->getClients());
	}

	if (command == "PART")
	{
		buf = buf.substr(space + 1, buf.length() - (space + 3));
		//_part.execute(buf, cli, channels);
	}

	if (command == "EXIT")
		std::exit(0);

	//if (command == "QUIT")
		//_quit.execute(buf, cli, channels);
}

void	parser::setServ(server *serv)
{
	_serv = serv;
}