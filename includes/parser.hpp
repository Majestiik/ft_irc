#pragma once

#include <iostream>

class server;
class client;

class parser{
	private:
		parser(parser const& other);
		parser	operator=(parser const& other);

	public:
		parser();
		~parser();
		void	parse(char *buffer, client *cli);
};

#include "server.hpp"
#include "client.hpp"