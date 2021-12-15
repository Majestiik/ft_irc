#pragma once

#include <iostream>

class parser{
	private:
		parser();
		parser(parser const& other);
		parser	operator=(parser const& other);

	public:
		parser(int sd, char *buffer);
		~parser();
};