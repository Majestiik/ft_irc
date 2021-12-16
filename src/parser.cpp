#include "../includes/parser.hpp"

parser::parser()
{
}

parser::~parser()
{
}


void	parser::parse(char *buffer, client *cli)
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
		buf = buf.substr(space + 1, buf.length() - (space + 3));
		std::cout << "channel name : " << buf << std::endl;
		std::string message = ":127.0.0.1 332 " + buf + "\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
	}

	if (command == "EXIT")
		std::exit(0);
}