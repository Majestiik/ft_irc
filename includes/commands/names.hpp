#pragma once

#include "command.hpp"

class names : public command
{
	public :
		names();
		~names();

		void execute(std::string buf, client *cli, std::vector<channel *> *channels);
};