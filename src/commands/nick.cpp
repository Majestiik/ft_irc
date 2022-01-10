#include "../../includes/commands/nick.hpp"

nick ::nick()
{
}

nick ::~nick()
{
}

bool	nick::_checkUser(std::string user, std::vector<client *> *clients)
{
	for (std::vector<client *>::iterator it = clients->begin(); it != clients->end(); it++)
	{
		client *c = *it;
		if (c->getNick() == user)
			return false;
	}
	return true;
}

bool	nick::_alreadyInformed(client *dest, std::vector<client *> informed)
{
	for (std::vector<client *>::iterator it = informed.begin(); it != informed.end(); it++)
	{
		client *search = *it;
		if (search->getNick() == dest->getNick())
			return true;
	}
	return false;
}

void	nick::_informChange(std::string message, client *cli, std::vector<channel *> *channels)
{
	std::vector<client *> informed;

	for (std::vector<channel *>::iterator it = channels->begin(); it != channels->end(); it++)
	{
		channel *c = *it;
		if (c->isMember(cli->getNick()))
		{
			std::cout << "on avance bb\n";
			std::vector<client *> cls = c->getMembers();
			for (std::vector<client *>::iterator it2 = cls.begin(); it2 != cls.end(); it2++)
			{
				client *dest = *it2;
				if (!_alreadyInformed(dest, informed))
				{
					std::cout << "envoie du message a " << dest->getNick() << std::endl;
					send(dest->getSd(), message.c_str(), message.length(), 0);
					informed.push_back(dest);
				}
			}
		}
	}
}

bool	nick::_validChars(std::string nick)
{
	size_t i = 0;
	while (i < nick.length())
	{
		if (nick[i] <= 32 || nick[i] > 126 || nick[i] == ':')
			return false;
		i++;
	}
	return true;
}

void	nick::execute(std::string buf, client *cli, std::vector<channel *> *channels, std::vector<client *> *clients)
{
	std::string message;
	std::cout << "buf dans nick : |" << buf << "|" << std::endl;
	if (buf.find(' ') == buf.npos)
	{
		message = ":server " + std::string(ERR_NONICKNAMEGIVEN) + " nick: No nickname given\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return ;
	}

	int begin = buf.find(' ') + 1;
	int length = buf.find('\r') - begin;
	std::string nick = buf.substr(begin, length);
	if (nick[0] == ':')
		nick = nick.substr(1, nick.length() - 1);
	if (!_validChars(nick))
	{
		message = ":server " + std::string(ERR_ERRONEUSNICKNAME) + " nick: Erroneus nickname\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return ;
	}
	if (!_checkUser(nick, clients))
	{
		message = ":server " + std::string(ERR_NICKNAMEINUSE) + " nick: Nickname is already in use\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return ;
	}
	std::cout << "nick : |" << nick << "|\n";

	message = ":" + cli->getNick() + " NICK " + nick +"\r\n";
	cli->setNick(nick);

	_informChange(message, cli, channels);
}