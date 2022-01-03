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

client *channel::getCli(std::string cli)
{
	for (std::vector<client*>::const_iterator it = _members.begin(); it != _members.end(); it++)
	{
		client *c = *it;
		if (c->getNick() == cli)
			return c;
	}
	return NULL;
}

void		channel::setName(std::string name)
{
	_name = name;
}

void		channel::setPassword(std::string password)
{
	_password = password;
}

void		channel::setMode(char mode, bool state)
{
	if (mode == 'p')
		isPrivate = state;
	else if (mode == 's')
		isSecrect = state;
	else if (mode == 't')
		isTopicLimited  = state;
	else if (mode == 'n')
		isExtMessAllow = state;
	else if (mode == 'm')
		isModerated = state;
	else if (mode == 'i')
		isInviteOnly = state;
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
	{
		//cli->setNick("#" + cli->getNick());
		_op.push_back(cli);
	}
}

void		channel::addBan(client *cli)
{
	if (isMember(cli))
	{
		_banned.push_back(cli);
	}
}

void		channel::addCanSpeak(client *cli)
{
	if (isMember(cli))
	{
		_canSpeakOnModerated.push_back(cli);
	}
}

void		channel::addInvisible(client *cli)
{
	if (isMember(cli))
	{
		_invisibles.push_back(cli);
	}
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
			_op.erase(it);
			break ;
		}
	}
}

void		channel::deleteCanSpeak(client *cli)
{
	for (std::vector<client *>::iterator it = _canSpeakOnModerated.begin(); it != _canSpeakOnModerated.end(); it++)
	{
		if (*it == cli)
		{
			_canSpeakOnModerated.erase(it);
			break ;
		}
	}
}

void		channel::deleteBan(client *cli)
{
	for (std::vector<client *>::iterator it = _banned.begin(); it != _banned.end(); it++)
	{
		if (*it == cli)
		{
			_banned.erase(it);
			break ;
		}
	}
}

void		channel::deleteInvisible(client *cli)
{
	for (std::vector<client *>::iterator it = _invisibles.begin(); it != _invisibles.end(); it++)
	{
		if (*it == cli)
		{
			_invisibles.erase(it);
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

bool		channel::isMember(std::string cli) const
{
	for (std::vector<client*>::const_iterator it = _members.begin(); it != _members.end(); it++)
	{
		client *c = *it;
		if (c->getNick() == cli)
			return true;
	}
	return false;
}

bool		channel::isOp(client *cli) const
{
	for (std::vector<client*>::const_iterator it = _op.begin(); it != _op.end(); it++)
	{
		client *c = *it;
		std::cout << "IS OP NAME : c nickname = " + c->getNick() + " cli nickname = " + cli->getNick() << std::endl;
		if (c->getNick() == cli->getNick())
			return true;
	}
	return false;
}

bool		channel::isBanned(client *cli) const
{
	for (std::vector<client*>::const_iterator it = _banned.begin(); it != _banned.end(); it++)
	{
		client *c = *it;
		if (c->getNick() == cli->getNick())
			return true;
	}
	return false;
}

bool		channel::isMode(char mode)
{
	if (mode == 'p' && isPrivate)
		return true;
	else if (mode == 's' && isSecrect)
		return true;
	else if (mode == 't' && isTopicLimited)
		return true;
	else if (mode == 'n' && isExtMessAllow)
		return true;
	else if (mode == 'm' && isModerated)
		return true;
	else if (mode == 'i' && isInviteOnly)
		return true;
	return false;
}