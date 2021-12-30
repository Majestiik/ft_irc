#pragma once
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <map>

#include "client.hpp"
#include "channel.hpp"
#include "parser.hpp"
#include "commands/privmsg.hpp"

//class parser;

class server
{
	private:
		server();
		server(server const& other);
		server	operator=(server const& other);
		int masterSocket;
		int addrlen;
		int newSocket;
		int activity;
		int valread;
		int sd;
		int maxSd;
		struct sockaddr_in address;
		char	buffer[1024];
		std::string	message;
		fd_set	readfds;
		bool	online;
		std::vector<client *> cls;
		parser pars;
		std::vector<channel *> chl;
		void	_incomingConnexion();
		void	_ioOperation();

	public:
		server(char **av);
		~server();
		void	start();
		std::vector<client *> *getClients();

};

