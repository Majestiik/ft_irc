#pragma once

#include <iostream>

class server;
class client;
class channel;

class parser{
	private:
		parser(parser const& other);
		parser	operator=(parser const& other);

	public:
		parser();
		~parser();
		void	parse(char *buffer, client *cli, channel *channels);
};

#include "server.hpp"
#include "client.hpp"
#include "channel.hpp"