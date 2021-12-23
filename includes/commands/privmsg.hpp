#pragma once

#include <iostream>
#include <sys/socket.h>

#include "../../includes/reply_codes.hpp"
#include "../client.hpp"
#include "../channel.hpp"

class privmsg
{
	private :
		std::vector<std::string> cmd;
		void getCmd(std::string buf);

	public :
		privmsg();
		~privmsg();

		void execute(std::string buf, client *cli, channel *chan);
};