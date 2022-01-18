#pragma once

#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <ctime>

#include "client.hpp"
//#include "channel.hpp"
#include "reply_codes.hpp"
//#include "commands/command.hpp"

class bot
{
	private:
		std::string	_name;
		bool _isActive;
		bot(bot const& other);
		bot operator=(bot const& other);
		void _talk(std::vector<std::string> _cmd, std::string cli, int cli_sd, std::string chan);
		void _help(std::vector<std::string> _cmd, std::string cli, int cli_sd, std::string chan);
		void _on(std::vector<client*> members, std::string chan);
		void _off(std::vector<client*> members, std::string chan);


	public:
		
		bot();
		~bot();

		std::string	getName() const;
		bool 		getIsActive() const;

		void		setName(std::string name);
		void		setActive(bool state);

		void		execute(std::vector<std::string> _cmd, std::string cli, int cli_sd, std::string chan, std::vector<client*> members);
		void		welcomeMsg(std::string cli, std::string chan, std::vector<client*> members);
};