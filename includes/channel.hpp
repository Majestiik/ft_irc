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
		bool _isPrivate;
		bool _isSecrect;
		bool _isTopicLimited;
		bool _isExtMessAllow;
		bool _isModerated;
		bool _isInviteOnly;
		int _limit_nbr;
		client *_creator;
		std::vector<client*> _members;
		std::vector<client*> _op;
		std::vector<client*> _banned;
		std::vector<client*> _canSpeakOnModerated;
		std::vector<client*> _invisibles;
		channel();
		channel(channel const& other);
		channel	operator=(channel const& other);

	public:
		channel(std::string name);
		~channel();

		std::string	getName() const;
		std::string	getPassword() const;
		std::vector<client*>	getMembers();
		client *getCli(std::string cli);
	
		void		setName(std::string name);
		void		setPassword(std::string password);
		void		setMode(char mode, bool state);
		void		addClient(client *cli);
		void		addOp(client *cli);
		void		addBan(client *cli);
		void		addCanSpeak(client *cli);
		void		addInvisible(client *cli);
		void		deleteClient(client *cli);
		void		deleteOp(client *cli);
		void		deleteBan(client *cli);
		void		deleteCanSpeak(client *cli);
		void		deleteInvisible(client *cli);
		std::string	listClients();
		bool		isMember(client *cli) const;
		bool		isMember(std::string cli) const;
		bool		isOp(client *cli) const;
		bool		isMode(char mode);
};


