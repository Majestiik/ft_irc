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
		client *_creator;
		std::vector<client*> _members;
		std::vector<client*> _op;
		channel();


	public:
		channel(std::string name, client *cli);

		~channel();
		std::string	getName() const;
		std::string	getPassword() const;
		std::vector<client*>	getMembers();
		bool		getExists() const;
		void		setName(std::string name);
		void		setPassword(std::string password);
		void		addClient(client *cli);
		void		deleteClient(client *cli);
		std::string	listClients();
};


