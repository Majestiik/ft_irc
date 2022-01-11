#pragma once

#include "command.hpp"

class list : public command
{
	public :
		list();
		~list();

		void execute(std::string buf, client *cli, std::vector<channel *> *channels);
};