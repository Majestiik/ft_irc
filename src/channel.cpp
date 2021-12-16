#include "../includes/channel.hpp"

channel::channel()
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

void		channel::setName(std::string name)
{
	_name = name;
}

void		channel::setPassword(std::string password)
{
	_password = password;
}