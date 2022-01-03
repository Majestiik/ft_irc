#include "../includes/server.hpp"

server::server(char **av)
{
	pars.setServ(this);
	_pass = av[2];

	//create a master socket
	if ( (masterSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		std::exit(EXIT_FAILURE);
		std::cerr << "Socker failed" << std::endl;
	}

	//set master socket to allow multiple connections (avoid address already in use pbs)
	int enable = 1;
	if (setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
	{
		std::exit(EXIT_FAILURE);
		std::cerr << "setsockopt(SO_REUSEADDR) failed" << std::endl;
	}

	//type of socket created
	int			port = std::atoi(av[1]);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	//bind the socket to localhost port 8080
	if (bind(masterSocket, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		std::exit(EXIT_FAILURE);
		std::cerr << "bind failed" << std::endl;
	}
	std::cout << "listener on port " << port << std::endl;

	//try to specify maximum of 3 pending connections for the master socket
	if (listen(masterSocket, 3) < 0)
	{
		std::exit(EXIT_FAILURE);
		std::cerr << "listen" << std::endl;
	}

	//accept the incoming connection
	std::cout << "waiting for connections..." << std::endl;
}

server::~server()
{
}

void	server::start()
{
	int maxSd;
	int	sd;
	int	activity;

	while (true)
	{
		//clear the socket set
		FD_ZERO(&readfds);

		//add master socket to set
		FD_SET(masterSocket, &readfds);
		maxSd = masterSocket;

		for(std::vector<client *>::iterator it = clients.begin(); it != clients.end(); it++)
		{
			client *c = *it;
			sd = c->getSd();

			//if valid socket descriptor then aff to read list
			if (sd > 0)
				FD_SET(sd, &readfds);
			
			//highest file descriptor number, need it for the select function
			if (sd > maxSd)
				maxSd = sd;

		}

		//wait for an activity on one of the socketsm timeout is NULL
		//so wait indefinitely
		activity = select(maxSd + 1, &readfds, NULL, NULL, NULL);

		if ((activity < 0) && (errno!=EINTR))
			std::cerr << "select error" << std::endl;

		//if something happens on the master socket,
		//then it's an incoming connexion
		if (FD_ISSET(masterSocket, &readfds))
			_incomingConnexion();
		//else its some IO operation one some other socket
		_ioOperation();
	}
}

void	server::_incomingConnexion()
{
	int newSocket;
	int addrlen = sizeof(address);

	if ((newSocket = accept(masterSocket, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
	{
		std::cerr << "accept" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	//inform user f socket number - used in send and receive commands
	std::cout << "New connection, socket fd is " << newSocket << " ip is " << inet_ntoa(address.sin_addr) << " port : " << ntohs(address.sin_port) << std::endl;

	//add new socket to array of sockets
	clients.push_back(new client(newSocket, address));
}

void	server::_ioOperation()
{
	int sd;
	int valread;
	int addrlen = sizeof(address);
	char	buffer[1024];

	for (std::vector<client *>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		client *c = *it;
		sd = c->getSd();

		if (FD_ISSET(sd, &readfds))
		{
			
			if ((valread = read(sd, buffer, 1024)) == 0)
			{
				//somebody disconnected, get his details and print
				getpeername(sd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
				std::cout << "Host disconnected, ip " << inet_ntoa(address.sin_addr) << " port " << ntohs(address.sin_port) << std::endl;

				//close tge socket and mark as 0 in list for reuse
				close(sd);
				//clients.erase(it);
			}
			else
			{
				buffer[valread] = '\0';
				std::cout << "===BUFFER : " << buffer << std::endl;
				std::string buf = buffer;
				int space = buf.find(' ');
				std::string command = buf.substr(0, space);
				if (command == "PASS")
				{
					std::string str = buf.substr(5, buf.length() - 7);
					std::cout << "str : |" << str << "|" << std::endl;
					if (str != _pass)
					{
						std::cout << "Wrong password" << std::endl;
						std::string err2 = ":server " + std::string(ERR_PASSWDMISMATCH) + " pass :Password incorrect\r\n";
						send(sd, err2.c_str(), err2.length(), 0);
						close(sd);
					}
					else
						(c->setAccept(true));
				}
				if (c->getAccept() == true)
					pars.parse(buf, c);
				else
				{
					std::string err = ":server " + std::string(ERR_NEEDMOREPARAMS) + " pass :Not enough parameters\r\n";
					send(sd, err.c_str(), err.length(), 0);
					close(sd);
				}
			}
		}
	}
}

std::vector<client *> *server::getClients()
{
	return (&clients);
}
