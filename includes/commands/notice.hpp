#pragma once

#include "command.hpp"


class notice : public command
{
	private :
		notice(notice const& other);
		notice	operator=(notice const& other);

	public :
		notice();
		~notice();
		void execute(std::string buf, client *cli, std::vector<channel *> *channels, std::vector<client *> *cli_list);
};