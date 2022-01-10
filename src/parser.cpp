#include "../includes/parser.hpp"

parser::parser()
{
}

parser::~parser()
{
}

std::string	parser::_detectUser(std::string buf, std::string *command)
{
	buf = buf.substr(buf.find('\n') +1 , buf.length() - buf.find('\n') +1 );
	if (buf.substr(0, 4) == "USER")
		*command = "USER";

	return buf;
}

void	parser::parse(std::string buf, client *cli)
{
	int space = buf.find(' ');

	std::string command = buf.substr(0, space);

	while (command.back() == '\n' || command.back() == '\r')
		command.pop_back();

	std::cout << BOLDRED << "command = |" << command << "|" << RESET << std::endl;

	if(command == "PASS")
	{
		std::string err = ":server " + std::string(ERR_ALREADYREGISTRED) + " pass :You may not reregister\r\n";
		send(cli->getSd(), err.c_str(), err.length(), 0);
	}
	if (command == "NICK")
	{
		_nick.execute(buf, cli, &channels, _serv->getClients());
		buf = _detectUser(buf, &command);
	}

	if (command == "USER")
	{
		_user.execute(buf, cli);
		/*
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
			std::cout << "Welcome message sent successfully" << std::endl;*/
	}

	if (command == "INVITE")
	{
		_invite.execute(buf, cli, &channels, _serv->getClients());
	}

	if (command == "JOIN")
	{
		buf = buf.substr(space + 1, buf.length() - (space + 3));
		_join.execute(buf, cli, &channels);
	}

	if (command == "PRIVMSG")
	{
		_privmsg.execute(buf, cli, &channels, _serv->getClients());
	}

	if (command == "PART")
	{
		buf = buf.substr(space + 1, buf.length() - (space + 3));
		_part.execute(buf, cli, &channels);
	}
	
	if (command == "MODE")
	{
		_mode.execute(buf, cli, &channels);
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