#pragma once

#include <iostream>
#include <sstream>
#include <sys/socket.h>

#include "../reply_codes.hpp"
//#include "../client.hpp"
#include "../channel.hpp"


class privmsg
{
	private :
		std::vector<std::string> cmd;
		void getCmd(std::string buf);
		channel*	_getChan(std::string name, std::vector<channel *> channels);

	public :
		privmsg();
		~privmsg();

		void execute(std::string buf, client *cli, std::vector<channel *> channels, client *cli_list);
};