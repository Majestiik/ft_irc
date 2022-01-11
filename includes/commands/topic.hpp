#pragma once

#include "command.hpp"

class topic : public command
{
	private :
		void getCmd(std::string buf);

	public :
		topic();
		~topic();

		void execute(std::string buf, client *cli, std::vector<channel *> *channels);
};