#pragma once

#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <ctime>

#include "client.hpp"
#include "channel.hpp"
#include "reply_codes.hpp"
#include "commands/command.hpp"

class bot : public command
{
	private:
		std::string	_name;
		bot(bot const& other);
		bot operator=(bot const& other);
		void _talk(client *cli, channel *chan);

	public:
		
		bot();
		~bot();
		std::string	getName() const;

		void		setName(std::string name);
		void		execute(std::string buf, client *cli, std::vector<channel *> *channels)	;
};