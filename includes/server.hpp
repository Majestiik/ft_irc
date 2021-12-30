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

class server
{
	private:
		int						masterSocket;
		struct sockaddr_in		address;
		fd_set					readfds;
		parser					pars;
		std::vector<client *>	clients;

		server();
		server(server const& other);
		server	operator=(server const& other);
		void	_incomingConnexion();
		void	_ioOperation();

	public:
		server(char **av);
		~server();
		void					start();
		std::vector<client *>	*getClients();
};

