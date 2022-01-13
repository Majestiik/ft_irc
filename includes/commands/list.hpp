#pragma once

#include "command.hpp"

class list : public command
{
	private :
		list(list const& other);
		list	operator=(list const& other);

	public :
		list();
		~list();
		void execute(std::string buf, client *cli, std::vector<channel *> *channels);
};