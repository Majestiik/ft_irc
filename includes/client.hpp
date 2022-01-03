#pragma once

#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>

class client
{
	private:
		std::string	_nick;
		std::string	_login;
		std::string	_realName;
		int			_sd;
		sockaddr_in	_address;
		std::vector<std::string> _chan_invitation;
		client(client const& other);
		client operator=(client const& other);

	public:
		client();
		client(int sd);
		client(int sd, sockaddr_in address);
		//~client();
		std::string	getNick() const;
		std::string	getLogin() const;
		std::string	getRealName() const;
		std::string	getIp() const;
		int			getSd() const;
		void		setNick(std::string nick);
		void		setLogin(std::string login);
		void		setRealName(std::string realName);
		void		setSd(int sd);
		void		setAddr(sockaddr_in address);
		void		addChanInvitation(std::string name);
		bool		isInvited(std::string name);
};