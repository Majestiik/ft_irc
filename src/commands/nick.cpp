#include "../../includes/commands/nick.hpp"

nick ::nick()
{
}

nick ::~nick()
{
}

bool	_checkUser(std::string user, std::vector<client *> *clients)
{
	for (std::vector<client *>::iterator it = clients->begin(); it != clients->end(); it++)
	{
		client *c = *it;
		if (c->getNick() == user)
			return false;
	}
	return true;
}

bool	_alreadyInformed(client *dest, std::vector<client *> informed)
{
	for (std::vector<client *>::iterator it = informed.begin(); it != informed.end(); it++)
	{
		client *search = *it;
		if (search->getNick() == dest->getNick())
			return true;
	}
	return false;
}

void	_informChange(std::string message, client *cli, std::vector<channel *> *channels)
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



bool	nick::execute(std::string buf, client *cli, std::vector<channel *> *channels)
{
	//int space = 0;
	bool ret = false;
	std::cout << "buf dans nick : |" << buf << "|" << std::endl;
	int begin = buf.find(' ') + 1;
	int length = buf.find('\r') - begin;
	std::string nick = buf.substr(begin, length);
	std::cout << "nick : |" << nick << "|\n";
	std::string message = ":" + cli->getNick() + " NICK " + nick +"\r\n";
	cli->setNick(nick);

	_informChange(message, cli, channels);
	return ret;
}