#pragma once
#include "command.hpp"

class dcc : public command
{
	private:

	public:
		void	execute(std::string buf, client *cli, std::vector<client *> *clients);
};