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
		client *_creator;
		std::vector<client*> _members;
		std::vector<client*> _op;
		std::vector<client*> _banned;
		std::vector<client*> _canSpeakOnModerated;
		std::vector<client*> _invisibles;
		bool _isPrivate;
		bool _isSecret;
		bool _isTopicLimited;
		bool _isExtMessAllow;
		bool _isModerated;
		bool _isInviteOnly;
		size_t _limit_nbr;
		channel();
		channel(channel const& other);
		channel	operator=(channel const& other);

	public:
		channel(std::string name);
		~channel();

/*****GETTERS*****/

		std::string	getName() const;
		std::string	getPassword() const;
		std::string getTopic() const;
		std::vector<client*>	getMembers();
		client *getCli(std::string cli);
		bool	getPrivate() const;
		bool	getSecret() const;
		bool	getTopicLimited() const;
		bool	getExtMessAllow() const;
		bool	getModerated() const;
		bool	getInviteOnly() const;
		size_t	getLimitNbr() const;

/*****SETTERS*****/
	
		void		setName(std::string name);
		void		setPassword(std::string password);
		void		setTopic(std::string topic);
		void		setMode(char mode, bool state);
		void		setPrivate(bool b);
		void		setSecret(bool b);
		void		setTopicLimited(bool b);
		void		setExtMessAllow(bool b);
		void		setModerated(bool b);
		void		setInviteOnly(bool b);
		void		setLimitNbr(size_t i);


/*****FONCTIONS****/
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
		void		deleteEverywhere(client *cli);
		std::string	listClients();
		bool		isMember(client *cli) const;
		bool		isMember(std::string cli) const;
		bool		isOp(client *cli) const;
		bool		isBanned(client *cli) const;
		bool		isCanSpeakM(client *cli) const;
		bool		isMode(char mode);
		std::string	getAllCurrentModes();
};


