#pragma once
#include <iostream>
#include <vector>
#include "client.hpp"

class channel
{
	private:
		std::string _topic;
		std::string	_name;
		std::string	_password;
		std::string	_mode;
		int _limit_nbr;
		client *_creator;
		std::vector<client*> _members;
		std::vector<client*> _op;
		std::vector<client*> _banned;
		channel();
		channel(channel const& other);
		channel	operator=(channel const& other);

	public:
		channel(std::string name);
		~channel();

		std::string	getName() const;
		std::string	getPassword() const;
		std::string	getMode() const;
		std::vector<client*>	getMembers();
		client *getCli(std::string cli);
	
		void		setName(std::string name);
		void		setPassword(std::string password);
		void		setMode(std::string mode);
		void		addClient(client *cli);
		void		addOp(client *cli);
		void		deleteClient(client *cli);
		void		deleteOp(client *cli);
		std::string	listClients();
		bool		isMember(client *cli) const;
		bool		isMember(std::string cli) const;
		bool		isOp(client *cli) const;
		bool		isMode(char mode);
};


