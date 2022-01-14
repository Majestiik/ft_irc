#include "../includes/channel.hpp"

channel::channel(std::string name):_name(name), _isPrivate(false), _isSecret(false), _isTopicLimited(false), _isExtMessAllow(false), _isModerated(false), _isInviteOnly(false), _limit_nbr(0)
{
	_topic = "Topic not set";
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

std::string channel::getTopic() const
{
	return _topic;
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

bool channel::getPrivate() const
{
	return _isPrivate;
}

bool channel::getSecret() const
{
	return _isSecret;
}

bool channel::getTopicLimited() const
{
	return _isTopicLimited;
}

bool channel::getExtMessAllow() const
{
	return _isExtMessAllow;
}

size_t channel::getLimitNbr() const
{
	return _limit_nbr;
}

bool channel::getInviteOnly() const
{
	return _isInviteOnly;
}

bool channel::getModerated() const
{
	return _isModerated;
}

void	channel::setPrivate(bool b)
{
	_isPrivate = b;
}

void	channel::setSecret(bool b)
{
	_isSecret = b;
}

void	channel::setTopicLimited(bool b)
{
	_isTopicLimited = b;
}

void	channel::setExtMessAllow(bool b)
{
	_isExtMessAllow = b;
}

void	channel::setLimitNbr(size_t i)
{
	_limit_nbr = i;
}

void	channel::setInviteOnly(bool b)
{
	_isInviteOnly = b;
}

void	channel::setModerated(bool b)
{
	_isModerated = b;
}

void		channel::setName(std::string name)
{
	_name = name;
}

void		channel::setPassword(std::string password)
{
	_password = password;
}

void		channel::setTopic(std::string topic)
{
	_topic = topic;
}

void		channel::setMode(char mode, bool state)
{
	if (mode == 'p')
		setPrivate(state);
	else if (mode == 's')
		setSecret(state);
	else if (mode == 't')
		setTopicLimited(state);
	else if (mode == 'n')
		setExtMessAllow(state);
	else if (mode == 'm')
		setModerated(state);
	else if (mode == 'i')
		setInviteOnly(state);
}

void		channel::addClient(client *cli)
{
	_members.push_back(cli);
}

void		channel::addOp(client *cli)
{
	if (isMember(cli))
	{
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

void		channel::deleteBan(std::string cli)
{
	for (std::vector<client *>::iterator it = _banned.begin(); it != _banned.end(); it++)
	{
		if ((*it)->getNick() == cli)
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

void		channel::deleteEverywhere(client *cli)
{
	deleteCanSpeak(cli);
	deleteClient(cli);
	deleteInvisible(cli);
	deleteOp(cli);
}

std::string	channel::listClients()
{
	std::string ret;
	for (std::vector<client *>::iterator it = _members.begin(); it != _members.end(); it++)
	{
		client *c = *it;
		if (isOp(c))
			ret += "@";
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

bool		channel::isBanned(std::string cli) const
{
	for (std::vector<client*>::const_iterator it = _banned.begin(); it != _banned.end(); it++)
	{
		client *c = *it;
		if (c->getNick() == cli)
			return true;
	}
	return false;
}

bool		channel::isCanSpeakM(client *cli) const
{
	for (std::vector<client*>::const_iterator it = _canSpeakOnModerated.begin(); it != _canSpeakOnModerated.end(); it++)
	{
		client *c = *it;
		if (c->getNick() == cli->getNick())
			return true;
	}
	return false;
}

bool		channel::isMode(char mode)
{
	if (mode == 'p' && getPrivate())
		return true;
	else if (mode == 's' && getSecret())
		return true;
	else if (mode == 't' && getTopicLimited())
		return true;
	else if (mode == 'n' && getExtMessAllow())
		return true;
	else if (mode == 'm' && getModerated())
		return true;
	else if (mode == 'i' && getInviteOnly())
		return true;
	return false;
}

std::string	channel::getAllCurrentModes()
{
	std::string allCurrentModes;

	allCurrentModes.push_back('+');

	if (getPrivate())
	{
		allCurrentModes.push_back('p');
	}
	if (getSecret())
	{
		allCurrentModes.push_back('s');
	}
	if (getInviteOnly())
	{
		allCurrentModes.push_back('i');
	}
	if (getTopicLimited())
	{
		allCurrentModes.push_back('t');
	}
	if (getExtMessAllow())
	{
		allCurrentModes.push_back('n');
	}
	if (getModerated())
	{
		allCurrentModes.push_back('m');
	}
	if (getLimitNbr() > 0)
	{
		allCurrentModes.push_back('l');
		allCurrentModes.append(std::to_string(_limit_nbr));
	}
	if (_password.size() > 0)
	{
		allCurrentModes.push_back('k');
	}

	return (allCurrentModes);
}