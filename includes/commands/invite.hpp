#pragma once

#include "command.hpp"

class invite : public command
{
	private:

	public:
		invite();
		void	execute(std::string buf, client *cli, std::vector<channel *> *channels, std::vector<client *> *cli_list);
		void	broadcastMsg(std::string buf, client *cli, channel *chan);
		~invite();
};