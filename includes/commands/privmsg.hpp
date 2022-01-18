#pragma once

#include "command.hpp"
#include "dcc.hpp"
#include "../bot.hpp"



class privmsg : public command
{
	private :
		privmsg(privmsg const& other);
		privmsg	operator=(privmsg const& other);

		bot	_bot;
		dcc _dcc;

	public :
		privmsg();
		~privmsg();
		void execute(std::string buf, client *cli, std::vector<channel *> *channels, std::vector<client *> *cli_list);

};