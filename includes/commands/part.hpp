#pragma once
#include <iostream>
#include <sys/socket.h>
//#include "../parser.hpp"
#include "../client.hpp"
#include "../channel.hpp"

class part
{
	private:
	int		_getChannel(std::string name, channel *chan);

	public:
		part();
		~part();
		void	execute(std::string buf, client *cli, channel *chan);
		void	broadcastMsg(std::string buf, client *cli, channel *chan);
};