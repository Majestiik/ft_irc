#pragma once

#include <iostream>
#include <vector>
#include "commands/invite.hpp"
#include "commands/join.hpp"
#include "commands/privmsg.hpp"
#include "commands/part.hpp"
#include "commands/mode.hpp"
#include "commands/quit.hpp"
#include "commands/nick.hpp"
#include "commands/user.hpp"
#include "commands/topic.hpp"
#include "commands/commandException.hpp"

class server;
class client;
class channel;

class parser{
	private:
		parser(parser const& other);
		parser	operator=(parser const& other);
		server	*_serv;
		invite	_invite;
		join	_join;
		privmsg _privmsg;
		part	_part;
		mode	_mode;
		quit	_quit;
		nick	_nick;
		user	_user;
		topic	_topic;

		std::vector<channel *>	channels;
		std::string				_detectUser(std::string buf, std::string *command);

	public:
		parser();
		~parser();
		void	parse(std::string buf, client *cli);
		void	setServ(server *serv);
};

#include "server.hpp"
#include "client.hpp"
#include "channel.hpp"
