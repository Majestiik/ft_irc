#pragma once

#include "command.hpp"

class topic : public command
{
	private :
		void getCmd(std::string buf);
		topic(topic const& other);
		topic	operator=(topic const& other);

	public :
		topic();
		~topic();
		void execute(std::string buf, client *cli, std::vector<channel *> *channels);
};