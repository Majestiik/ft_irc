#pragma once

#include "command.hpp"

class invite : public command
{
	private:
		invite(invite const& other);
		invite	operator=(invite const& other);
	public:
		invite();
		~invite();
		void	execute(std::string buf, client *cli, std::vector<channel *> *channels, std::vector<client *> *cli_list);
		void	broadcastMsg(std::string buf, client *cli, channel *chan);
};