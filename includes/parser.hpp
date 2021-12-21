#pragma once

#include <iostream>
#include "commands/join.hpp"
#include "commands/part.hpp"

class server;
class client;
class channel;


class parser{
	private:
		parser(parser const& other);
		parser	operator=(parser const& other);
		server	*_serv;
		join	_join;
		part	_part;


	public:
		parser();
		~parser();
		void	parse(char *buffer, client *cli, channel *channels);
		void	setServ(server *serv);
};

#include "server.hpp"
#include "client.hpp"
#include "channel.hpp"
