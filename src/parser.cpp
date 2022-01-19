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

std::string parser::_convertCommand(std::string command)
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

	std::cout << BOLDMAGENTA << "command = |" << command << "|" << RESET << std::endl;

	if(command == "PASS")
	{
		std::string err = ":server " + std::string(ERR_ALREADYREGISTRED) + " pass :You may not reregister\r\n";
		send(cli->getSd(), err.c_str(), err.length(), 0);
	}
	else if (command == "NICK")
	{
		_nick.execute(buf, cli, &channels, _serv->getClients());
		buf = _detectUser(buf, &command);
		if (command == "USER")
			_user.execute(buf, cli);
	}
	else if (command == "USER")
		_user.execute(buf, cli);

	else if (command == "INVITE")
		_invite.execute(buf, cli, &channels, _serv->getClients());

	else if (command == "JOIN")
		_join.execute(buf, cli, &channels);

	else if (command == "PRIVMSG")
	{
		std::string ret = _privmsg.execute(buf, cli, &channels, _serv->getClients());
		if (ret.size() > 0)
			_kick.execute(buf, cli, &channels, true, ret);
	}

	else if (command == "NOTICE")
		_notice.execute(buf, cli, &channels, _serv->getClients());

	else if (command == "PART")
		_part.execute(buf, cli, &channels);
	
	else if (command == "MODE")
		_mode.execute(buf, cli, &channels);

	else if (command == "TOPIC")
		_topic.execute(buf, cli, &channels);

	else if (command == "NAMES")
		_names.execute(buf, cli, &channels);

	else if (command == "LIST")
		_list.execute(buf, cli, &channels);

	else if (command == "KICK")
		_kick.execute(buf, cli, &channels, false, " ");

	else if (command == "EXIT")
		_serv->setOffline();

	else if (command == "QUIT")
		_quit.execute(buf, cli, &channels);

	else if (command != "PONG")
	{
		std::string message = ":server " + std::string(ERR_UNKNOWNCOMMAND) + " " + command + " :Unknown command\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
	}
}

void	parser::setServ(server *serv)
{
	_serv = serv;
}