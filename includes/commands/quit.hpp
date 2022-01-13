#pragma once
#include <iostream>
#include <sys/socket.h>
#include "../client.hpp"
#include "../channel.hpp"

class quit
{
	private:
	bool	_alreadyInformed(client *dest, std::vector<client *> informed);
	void	_informChange(std::string message, client *cli, std::vector<channel *> *channels);
	quit(quit const& other);
	quit	operator=(quit const& other);

	public:
		quit();
		~quit();
		void	execute(std::string buf, client *cli, std::vector<channel *> *chan);
};
