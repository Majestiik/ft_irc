#pragma once
#include "command.hpp"

class user : public command
{
	private:
		int		_nbArgs(std::string buf);
		user(user const& other);
		user	operator=(user const& other);

	public:
		user();
		~user();
		void	execute(std::string buf, client *cli);
};