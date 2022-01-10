#pragma once

#include "command.hpp"

class nick : public command
{
private:
	nick(nick const& other);
	nick	operator=(nick const& other);
	bool	_checkUser(std::string user, std::vector<client *> *clients);
	bool	_alreadyInformed(client *dest, std::vector<client *> informed);
	void	_informChange(std::string message, client *cli, std::vector<channel *> *channels);
	bool	_validChars(std::string nick);

public:
	nick();
	~nick();
	void execute(std::string buf, client *cli, std::vector<channel *> *channels, std::vector<client *> *clients);
};


