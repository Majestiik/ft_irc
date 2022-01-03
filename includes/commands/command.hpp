#pragma once

#include <iostream>
#include <sstream>
#include <sys/socket.h>

#include "../client.hpp"
#include "../channel.hpp"
#include "../reply_codes.hpp"

class command
{
	protected:
		channel*	_getChan(std::string name, std::vector<channel *> *channels);
		bool		_checkClient(client *cli, channel *chan);
	public:
		command();
		virtual ~command();
		
};