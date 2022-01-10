#pragma once

#include "command.hpp"

class nick : public command
{
private:
	/* data */
public:
	nick();
	~nick();
	bool execute(std::string buf, client *cli, std::vector<channel *> *channels);
};


