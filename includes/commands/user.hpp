#pragma once
#include "command.hpp"

class user : public command
{
	private:
		user(user const& other);
		user	operator=(user const& other);

	public:
		user();
		~user();
		void	execute();
};