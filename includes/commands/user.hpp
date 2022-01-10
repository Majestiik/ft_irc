#pragma once
#include "command.hpp"

class user : public command
{
	private:
		user(user const& other);
		user	operator=(user const& other);
		int		_nbArgs(std::string buf);

	public:
		user();
		~user();
		void	execute(std::string buf, client *cli);
};