#include "../includes/client.hpp"

client::client(): _sd(0)
{
}

client::client(int sd):_sd(sd)
{
}

//client::~client()
//{
//}

std::string	client::getNick() const
{
	return _nick;
}

std::string	client::getLogin() const
{
	return _login;
}

std::string	client::getRealName() const
{
	return _realName;
}

int			client::getSd() const
{
	return _sd;
}

void	client::setNick(std::string nick)
{
	_nick = nick;
}

void	client::setLogin(std::string login)
{
	_login = login;
}

void	client::setRealName(std::string realName)
{
	_realName = realName;
}

void	client::setSd(int sd)
{
	_sd = sd;
}