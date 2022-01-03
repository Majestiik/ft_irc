#pragma once

#include "command.hpp"

class part : public command
{
	private:
	//channel*	_getChan(std::string name, std::vector<channel *> *channels);
	//bool		_checkClient(client *cli, channel *chan);

	public:
		part();
		~part();
		void	execute(std::string buf, client *cli, std::vector<channel *> *chan);
};