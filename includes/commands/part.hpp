#pragma once

#include "command.hpp"

class part : command
{
	private:
	//channel*	_getChan(std::string name, std::vector<channel *> *channels);
	//bool		_checkClient(client *cli, channel *chan);

	public:
		part();
		~part();
		void	execute(std::string buf, client *cli, std::vector<channel *> *chan);
		void	broadcastMsg(std::string buf, client *cli, channel *chan);
};