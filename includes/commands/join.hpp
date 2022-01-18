#pragma once

#include "command.hpp"
#include "../bot.hpp"

class join : public command
{
	private:
		bool	_checkName(std::string name, std::vector<channel *> *channels);
		void	_joinChan(std::string name, client *cli, std::vector<channel *> *channels);
		void	_informMembers(std::string name, client *cli, channel *chan);
		join(join const& other);
		join	operator=(join const& other);

		bot	_bot;

	public:
		join();
		~join();
		void	execute(std::string buf, client *cli, std::vector<channel *> *channels);
};
