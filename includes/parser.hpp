#pragma once

#include <iostream>
#include "commands/join.hpp"
#include "commands/privmsg.hpp"
#include "commands/part.hpp"
#include "commands/quit.hpp"

class server;
class client;
class channel;


class parser{
	private:
		parser(parser const& other);
		parser	operator=(parser const& other);
		server	*_serv;
		join	_join;
		privmsg _privmsg;
		part	_part;
		quit	_quit;


	public:
		parser();
		~parser();
		void	parse(std::string buf, client *cli, channel *channels);
		void	setServ(server *serv);
};

#include "server.hpp"
#include "client.hpp"
#include "channel.hpp"
