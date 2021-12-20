#pragma once
#include <iostream>
#include <vector>
#include "client.hpp"

class channel
{
	private:
		std::string	_name;
		std::string	_password;
		bool		_exists;
		channel(channel const& other);
		channel	operator=(channel const& other);
		std::vector<client*> members;


	public:
		channel(std::string name);
		channel();
		~channel();
		std::string	getName() const;
		std::string	getPassword() const;
		bool		getExists() const;
		void		setName(std::string name);
		void		setPassword(std::string password);
		void		setExists(bool b);
		void		addClient(client *cli);
		void		deleteClient(client *cli);
		void		create();
		std::string	listClients();
};


