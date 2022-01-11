#include "../../includes/commands/nick.hpp"

nick ::nick()
{
}

nick ::~nick()
{
}

bool	nick::_checkUser(std::string user, std::vector<client *> *clients)
{
	std::cout << "==list of nicks :==\n";
	for (std::vector<client *>::iterator it = clients->begin(); it != clients->end(); it++)
	{
		client *c = *it;
		std::cout << c->getNick() << std::endl;
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
			std::vector<client *> cls = c->getMembers();
			for (std::vector<client *>::iterator it2 = cls.begin(); it2 != cls.end(); it2++)
			{
				client *dest = *it2;
				if (!_alreadyInformed(dest, informed))
				{
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
		throw commandException::nick_no_nick();
		/*message = ":server " + std::string(ERR_NONICKNAMEGIVEN) + " nick: No nickname given\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return ;*/
	}

	int begin = buf.find(' ') + 1;
	int length = buf.length() - begin - 1;
	if (buf.find('\r') != buf.npos)
		length = buf.find('\r') - begin;
		
	std::cout << "begin - length : " << begin << " - " << length << std::endl;
	std::string nick = buf.substr(begin, length);
	if (nick[0] == ':')
		nick = nick.substr(1, nick.length() - 1);
	std::cout << "nick apres parsing : |" << nick << "|" << std::endl;
	if (!_validChars(nick))
	{
		throw commandException::nick_erroneus();
		//message = ":server " + std::string(ERR_ERRONEUSNICKNAME) + " nick: Erroneus nickname\r\n";
		//send(cli->getSd(), message.c_str(), message.length(), 0);
		//return ;
	}
	if (!_checkUser(nick, clients))
	{
		//while (!_checkUser(nick, clients))
		//	nick += '_';
		//std::cout << "nick apres boucle " << nick << std::endl;
		//message = ":" + cli->getNick() + " NICK " + nick +"\r\n";
		//cli->setNick(nick);
		throw commandException::nick_inuse();
		//std::cout << "ca degage ou pas\n";
		//message = ":server " + std::string(ERR_NICKNAMEINUSE) + " nick: Nickname is already in use\r\n";
		//send(cli->getSd(), message.c_str(), message.length(), 0);
		//return ;
	}
	std::cout << "nick avant set : |" << nick << "|\n";

	message = ":" + cli->getNick() + " NICK " + nick +"\r\n";
	cli->setNick(nick);

	_informChange(message, cli, channels);
}