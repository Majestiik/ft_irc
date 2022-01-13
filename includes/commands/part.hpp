#pragma once

#include "command.hpp"

class part : public command
{
	private:
		part(part const& other);
		part	operator=(part const& other);

	public:
		part();
		~part();
		void	execute(std::string buf, client *cli, std::vector<channel *> *channels);
};