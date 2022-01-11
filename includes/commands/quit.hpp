#pragma once
#include <iostream>
#include <sys/socket.h>
//#include "../parser.hpp"
#include "../client.hpp"
#include "../channel.hpp"

class quit
{
	private:
	bool	_alreadyInformed(client *dest, std::vector<client *> informed);
	void	_informChange(std::string message, client *cli, std::vector<channel *> *channels);

	public:
		quit();
		~quit();
		void	execute(std::string buf, client *cli, std::vector<channel *> *chan);
		//void	broadcastMsg(std::string buf, client *cli, channel *chan);
};
