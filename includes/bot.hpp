#pragma once

#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <ctime>

#include "client.hpp"
//#include "channel.hpp"
#include "reply_codes.hpp"
//#include "commands/command.hpp"

class bot
{
	private:
		std::string	_name;
		bool _isActive;
		std::vector<std::string> _banWordsList;
		bool _isBanWActive;
		bot(bot const& other);
		bot operator=(bot const& other);
		void _talk(std::vector<std::string> _cmd, std::string cli, int cli_sd, std::string chan);
		void _help(std::vector<std::string> _cmd, std::string cli, int cli_sd, std::string chan);
		void _on(std::vector<client*> members, std::string chan);
		void _off(std::vector<client*> members, std::string chan);
		void _banWOn(int cli_sd, std::string chan);
		void _banWOff(int cli_sd, std::string chan);
		void _banWords(std::vector<std::string> _cmd, std::string cli, int cli_sd, std::string chan);


	public:
		
		bot();
		~bot();

		std::string	getName() const;
		bool 		getIsActive() const;
		bool		getIsBanWActive() const;
		std::string	getBanWords() const;

		void		setName(std::string name);
		void		setActive(bool state);
		void		setBanWActive(bool state);
		void		addBanWord(std::string banWord);
		int			delBanWord(std::string banWord);
		bool		isBanWorld(std::string message);

		void		execute(std::vector<std::string> _cmd, std::string cli, int cli_sd, std::string chan, std::vector<client*> members);
		void		welcomeMsg(std::string cli, std::string chan, std::vector<client*> members);
};