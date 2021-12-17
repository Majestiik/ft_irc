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