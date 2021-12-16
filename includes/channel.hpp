#pragma once
#include <iostream>
#include <vector>
#include "client.hpp"

class channel
{
	private:
		std::string	_name;
		std::string	_password;
		channel(channel const& other);
		channel	operator=(channel const& other);
		std::vector<client *> members;


	public:
		channel();
		~channel();
		std::string	getName() const;
		std::string	getPassword() const;
		void		setName(std::string name);
		void		setPassword(std::string password);
};


