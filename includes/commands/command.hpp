#pragma once

#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <ctime>

#include "../client.hpp"
#include "../channel.hpp"
#include "../reply_codes.hpp"

class command
{
	protected:
		std::vector<std::string> _cmd;

		channel*	_getChan(std::string name, std::vector<channel *> *channels);
		bool		_checkClient(client *cli, channel *chan);
		void		_getCmd(std::string buf);
	public:
		command();
		virtual ~command();
		
};