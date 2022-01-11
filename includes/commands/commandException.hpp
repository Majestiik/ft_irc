#pragma once
#include <iostream>

class commandException
{
public:
	class pass_registred : public std::exception
	{
		const char *what() const throw()
		{
			std::string message = ":server " + std::string(ERR_ALREADYREGISTRED) + " pass :You may not reregister\r\n";
			return message.c_str();
		}
	};

	class nick_no_nick : public std::exception
	{
		const char *what() const throw()
		{
			std::string message = ":server " + std::string(ERR_NONICKNAMEGIVEN) + " nick: No nickname given\r\n";
			return message.c_str();
		}
	};

	class nick_erroneus : public std::exception
	{
		const char *what() const throw()
		{
			std::string message = ":server " + std::string(ERR_ERRONEUSNICKNAME) + " nick: Erroneus nickname\r\n";
			return message.c_str();
		}
	};

	class nick_inuse : public std::exception
	{
		const char *what() const throw()
		{
			std::string message = ":server " + std::string(ERR_NICKNAMEINUSE) + " nick: Nickname is already in use\r\n";
			return message.c_str();
		}
	};

	class user_params : public std::exception
	{
		const char *what() const throw()
		{
			std::string message = ":server " + std::string(ERR_NEEDMOREPARAMS) + " user :Not enough parameters\r\n";
			return message.c_str();
		}
	};

	class user_registred : public std::exception
	{
		const char *what() const throw()
		{
			std::string message = ":server " + std::string(ERR_ALREADYREGISTRED) + " user :You may not reregister\r\n";
			return message.c_str();
		}
	};
};