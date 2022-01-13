#pragma once

#include "command.hpp"

class names : public command
{
	private:
		names(names const& other);
		names	operator=(names const& other);

	public :
		names();
		~names();
		void execute(std::string buf, client *cli, std::vector<channel *> *channels);
};