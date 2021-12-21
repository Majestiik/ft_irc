#include "../includes/server.hpp"

server::server(char **av)
{
	//parser parse;
	pars.setServ(this);
	online = true;
	message = ":127.0.0.1 001 leickmay :Welcome to the IRMEGASTONKS network, you'll see it's incredible\r\n";
	//initialise all clientSocket[] to 0 so not checked
	//for (int i = 0; i < maxClients; i++)
	//	clientSocket[i] = 0;

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
	addrlen = sizeof(address);
	std::cout << "waiting for connections..." << std::endl;
}

server::~server()
{
}

void	server::start()
{

	while (online)
	{
		//clear the socket set
		FD_ZERO(&readfds);

		//add master socket to set
		FD_SET(masterSocket, &readfds);
		maxSd = masterSocket;

		//add child sockets to set
		for (int i = 0; i < maxClients; i++)
		{
			//socket descriptor
			//sd = clientSocket[i];
			sd = clients[i].getSd();

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
	if ((newSocket = accept(masterSocket, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
	{
		std::cerr << "accept" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	//inform user f socket number - used in send and receive commands
	std::cout << "New connection, socket fd is " << newSocket << " ip is " << inet_ntoa(address.sin_addr) << " port : " << ntohs(address.sin_port) << std::endl;

	//send new connection greeting message
	if (send(newSocket, message.c_str(), message.length(), 0) != (long)message.length())
		std::cerr << "send" << std::endl;
	else
		std::cout << "Welcome message sent successfully" << std::endl;

	//add new socket to array of sockets
	for (int i = 0; i < maxClients; i++)
	{
		if (clients[i].getSd() == 0)
		{
			//clientSocket[i] = newSocket;
			std::cout << "Adding to list of sockets as " << i << std::endl;
			clients[i].setSd(newSocket);
			break ;
		}
	}
}

void	server::_ioOperation()
{
	for (int i = 0; i < maxClients; i++)
	{
		//sd = clientSocket[i];
		sd = clients[i].getSd();

		if (FD_ISSET(sd, &readfds))
		{
			//check if it was for closing, and also read the incoming message
			if ((valread = read(sd, buffer, 1024)) == 0)
			{
				//somebody disconnected, get his details and print
				getpeername(sd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
				std::cout << "Host disconnected, ip " << inet_ntoa(address.sin_addr) << " port " << ntohs(address.sin_port) << std::endl;

				//close tge socket and mark as 0 in list for reuse
				close(sd);
				//clientSocket[i] = 0;
				clients[i].setSd(0);
			}
			//Echo back the message that came in
			else
			{
				//set the string terminating NULL byte on the end of the data read
				buffer[valread] = '\0';
				send(sd, buffer, strlen(buffer), 0);
				std::cout << "===BUFFER : " << buffer << " SD : " << sd << std::endl;
				pars.parse(buffer, &clients[i], channels);
				std::cout << "parsed : i = " << i << " nick : " << clients[i].getNick() << \
				" login : " << clients[i].getLogin() << " real name : " << clients[i].getRealName() << std::endl;
				std::cout << "existing channels : " << std::endl;
				for (int j = 0; j < 30; j++)
				{
					if (channels[j].getExists() == true)
						std::cout << channels[j].getName() << std::endl;
				}
			}
		}
	}
}

