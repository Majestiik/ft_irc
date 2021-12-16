#pragma once
#include <iostream>

class client{
	private:
		std::string _nick;
		std::string _login;
		std::string _realName;
		int			_sd;
		client(client const& other);
		client operator=(client const& other);

	public:
		client();
		client(int sd);
		//~client();
		std::string getNick() const;
		std::string getLogin() const;
		std::string getRealName() const;
		int			getSd() const;
		void		setNick(std::string nick);
		void		setLogin(std::string login);
		void		setRealName(std::string realName);
		void		setSd(int sd);
};