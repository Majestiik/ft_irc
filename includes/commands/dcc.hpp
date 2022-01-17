#pragma once
#include "command.hpp"

class dcc : public command
{
	private:
		dcc(dcc const& other);
		dcc	operator=(dcc const& other);

	public:
		dcc();
		~dcc();
		void	execute(client *cli, std::vector<client *> *clients, std::vector<std::string> cmd);
};