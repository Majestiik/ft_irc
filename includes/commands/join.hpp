#pragma once
#include <iostream>
#include <sys/socket.h>
//#include "../parser.hpp"
#include "command.hpp"

class join
{
	private:
		bool	_checkName(std::string name, std::vector<channel *> channels);
		void	_joinChan(std::string name, client *cli, std::vector<channel *> channels);
		void	_informMembers(std::string name, client *cli, channel *chan);
		bool	_checkClient(client *cli, channel *chan);
		channel	*_getChan(std::string name, std::vector<channel *> channels);

	public:
		join();
		void	execute(std::string buf, client *cli, std::vector<channel *> channels);
		void	broadcastMsg(std::string buf, client *cli, channel *chan);
		~join();
};
