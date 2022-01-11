#include "../includes/parser.hpp"

parser::parser()
{
}

parser::~parser()
{
	channel *c;
	for (std::vector<channel *>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		c = *it;
		delete c;
	}
}

std::string	parser::_detectUser(std::string buf, std::string *command)
{
	buf = buf.substr(buf.find('\n') +1 , buf.length() - buf.find('\n') +1 );
	if (buf.substr(0, 4) == "USER")
		*command = "USER";

	return buf;
}

std::string _convertCommand(std::string command)
{
	command = command.substr(1, command.length() - 1);
	int i = 0;
	while (command[i])
	{
		if (command[i] >= 97 && command[i] <= 122)
			command[i] -= 32;
		i++;
	}
	return command;
}

void	parser::parse(std::string buf, client *cli)
{
	int space = buf.find(' ');

	std::string command = buf.substr(0, space);

	if (command[0] == '/')
	{
		command = _convertCommand(command);
		buf = buf.substr(1, buf.length() - 1);
	}

	while (command.back() == '\n' || command.back() == '\r')
		command.pop_back();

	std::cout << BOLDRED << "command = |" << command << "|" << RESET << std::endl;

	if(command == "PASS")
		throw commandException::pass_registred();
	//{
		//std::string err = ":server " + std::string(ERR_ALREADYREGISTRED) + " pass :You may not reregister\r\n";
		//send(cli->getSd(), err.c_str(), err.length(), 0);
	//}
	if (command == "NICK")
	{
		_nick.execute(buf, cli, &channels, _serv->getClients());
		buf = _detectUser(buf, &command);
	}

	if (command == "USER")
	{
		_user.execute(buf, cli);
	}

	if (command == "INVITE")
	{
		_invite.execute(buf, cli, &channels, _serv->getClients());
	}

	if (command == "JOIN")
	{
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
		_serv->setOffline();

	//if (command == "QUIT")
		//_quit.execute(buf, cli, channels);
}

void	parser::setServ(server *serv)
{
	_serv = serv;
}