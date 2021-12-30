#include "../includes/channel.hpp"

channel::channel(std::string name):_name(name)
{

}

channel::~channel()
{
}

std::string	channel::getName() const
{
	return _name;
}

std::vector<client*>	channel::getMembers()
{
	return _members;
}

std::string	channel::getPassword() const
{
	return _password;
}

std::string	channel::getMode() const
{
	return _mode;
}

void		channel::setName(std::string name)
{
	_name = name;
}

void		channel::setPassword(std::string password)
{
	_password = password;
}

void		channel::setMode(std::string mode)
{
	_mode = mode;
}

void		channel::addClient(client *cli)
{
	_members.push_back(cli);
	std::cout << "== Members vector : " << std::endl;
	for (std::vector<client*>::iterator it = _members.begin(); it != _members.end(); it++)
	{
		client *c = *it;
		std::cout << "- "<< c->getNick() << std::endl;
	}
}

void		channel::addOp(client *cli)
{
	if (isMember(cli))
		_op.push_back(cli);
}

void		channel::deleteClient(client *cli)
{
	for (std::vector<client *>::iterator it = _members.begin(); it != _members.end(); it++)
	{
		if (*it == cli)
		{
			_members.erase(it);
			break ;
		}
	}
}

void		channel::deleteOp(client *cli)
{
	for (std::vector<client *>::iterator it = _op.begin(); it != _op.end(); it++)
	{
		if (*it == cli)
		{
			_members.erase(it);
			break ;
		}
	}
}

std::string	channel::listClients()
{
	std::string ret;
	for (std::vector<client *>::iterator it = _members.begin(); it != _members.end(); it++)
	{
		client *c = *it;
		ret += c->getNick() + " ";
	}
	return ret;
}

bool		channel::isMember(client *cli) const
{
	for (std::vector<client*>::const_iterator it = _members.begin(); it != _members.end(); it++)
	{
		client *c = *it;
		if (c->getNick() == cli->getNick())
			return true;
	}
	return false;
}

bool		channel::isOp(client *cli) const
{
	for (std::vector<client*>::const_iterator it = _op.begin(); it != _op.end(); it++)
	{
		client *c = *it;
		if (c->getNick() == cli->getNick())
			return true;
	}
	return false;
}