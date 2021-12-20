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
		//nt clientSocket[30];
		static const int maxClients = 30;
		int activity;
		int valread;
		int sd;
		int maxSd;
		struct sockaddr_in address;
		char	buffer[1024];
		std::string	message;
		fd_set	readfds;
		bool	online;
		void	_incomingConnexion();
		void	_ioOperation();
		client	clients[maxClients];
		parser pars;
		channel channels[maxClients];
		//std::map<std::string, channel*> chan;



	public:
		server(char **av);
		~server();
		void	start();

};

