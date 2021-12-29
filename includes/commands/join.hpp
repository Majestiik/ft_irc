#pragma once
#include <iostream>
#include <sys/socket.h>
//#include "../parser.hpp"
#include "command.hpp"

class join
{
	private:
		bool	_checkName(std::string name, channel *chan);
		void	_join(std::string name, client *cli, channel *chan);
		void	_getOtherMembers(std::string name, client *cli, channel *chan, int i);
		void	_informOtherMembers(std::string name, client *cli, channel *chan, int i);
		bool	_checkClient(client *cli, channel *chan, int i);

	public:
		join();
		void	execute(std::string buf, client *cli, channel *chan);
		void	broadcastMsg(std::string buf, client *cli, channel *chan);
		~join();
};
