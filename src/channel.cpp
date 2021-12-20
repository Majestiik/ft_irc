#include "../includes/channel.hpp"

channel::channel(std::string name):_name(name),_exists(true)
{
}

channel::channel():_exists(false)
{
}

channel::~channel()
{
}

std::string	channel::getName() const
{
	return _name;
}

std::string	channel::getPassword() const
{
	return _password;
}

bool	channel::getExists() const
{
	return _exists;
}

void		channel::setName(std::string name)
{
	_name = name;
}

void		channel::setPassword(std::string password)
{
	_password = password;
}

void	channel::setExists(bool b)
{
	_exists = b;
}

void		channel::addClient(client *cli)
{
	members.push_back(cli);
	std::cout << "== Members vector : " << std::endl;
	for (std::vector<client*>::iterator it = members.begin(); it != members.end(); it++)
	{
		client *c = *it;
		std::cout << "- "<< c->getNick() << std::endl;
	}
}

void		channel::deleteClient(client *cli)
{
	for (std::vector<client *>::iterator it = members.begin(); it != members.end(); it++)
	{
		if (*it == cli)
		{
			members.erase(it);
			break ;
		}
	}
}

void		channel::create()
{
	
}

std::string	channel::listClients()
{
	std::string ret;
	for (std::vector<client *>::iterator it = members.begin(); it != members.end(); it++)
	{
		client *c = *it;
		ret += "@" + c->getNick() + " ";
	}
	return ret;
}