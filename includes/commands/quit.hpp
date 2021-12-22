#pragma once
#include <iostream>
#include <sys/socket.h>
//#include "../parser.hpp"
#include "../client.hpp"
#include "../channel.hpp"

class quit
{
	private:
	

	public:
		quit();
		~quit();
		void	execute(std::string buf, client *cli, channel *chan);
		//void	broadcastMsg(std::string buf, client *cli, channel *chan);
};
