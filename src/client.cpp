#include "../includes/client.hpp"

client::client(): _sd(0)
{
}

client::client(int sd):_sd(sd)
{
}

client::client(int sd, sockaddr_in address):_sd(sd), _address(address)
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

void	client::setAddr(sockaddr_in address)
{
	_address = address;
}

std::string	client::getIp() const
{
	std::string ip = inet_ntoa(_address.sin_addr);
	return ip;
}