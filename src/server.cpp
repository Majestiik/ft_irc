#include "../includes/server.hpp"

server::server(char **av)
{
	pars.setServ(this);
	_pass = av[2];

	//create a master socket
	if ( (masterSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		throw servException::socket_failure();

	//set master socket to allow multiple connections (avoid address already in use pbs)
	int enable = 1;
	if (setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
		throw servException::setsockopt_failure();

	//type of socket created
	int			port = std::atoi(av[1]);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr =  INADDR_ANY;
	address.sin_port = htons(port);

	//bind the socket to localhost port
	if (bind(masterSocket, (struct sockaddr *)&address, sizeof(address)) < 0)
		throw servException::bind_failure();

	std::cout << "listener on port " << port << std::endl;

	//try to specify maximum of 3 pending connections for the master socket
	if (listen(masterSocket, 3) < 0)
		throw servException::listen_failure();

	//accept the incoming connection
	std::cout << "waiting for connections..." << std::endl;
}

server::~server()
{
	client *c;
	for (std::vector<client *>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		c = *it;
		delete c;
	}
}

void	server::start()
{
	int maxSd;
	int	sd;
	int	activity;
	online = true;

	while (online)
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
		_operation();
	}
}

void	server::_incomingConnexion()
{
	int newSocket;
	int addrlen = sizeof(address);

	if ((newSocket = accept(masterSocket, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
		throw servException::accept_failure();

	//inform user f socket number - used in send and receive commands
	std::cout << "New connection, socket fd is " << newSocket << " ip is " << inet_ntoa(address.sin_addr) << " port : " << ntohs(address.sin_port) << std::endl;

	//add new socket to array of sockets
	clients.push_back(new client(newSocket, address));
}

void	server::_eraseClient(client *c)
{
	std::vector<client *>::iterator it = clients.begin();
	while (it != clients.end())
	{
		if (*it == c)
			break ;
		it++;
	}
	delete c;
	clients.erase(it);
}

void	server::_checkPass(client *c, std::string buf)
{
	std::string command = buf.substr(0, buf.find(' '));

	if (command == "/pass")
	{
		command = "PASS";
		buf = buf.substr(1, buf.length() - 1);
	}

	if (command == "PASS" || command == "/pass")
	{
		std::string pass = buf.substr(5, buf.length() - 6);
		if (buf.find('\r') != buf.npos)
			pass = buf.substr(5, buf.length() - 7);

		if (pass == _pass)
		{
			c->setAccept("true");
			return ;
		}
		else
			throw servException::pass_mismatch();
	}
	else
		throw servException::pass_param();

}

void	server::_operation()
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
				std::cout << "client disconnected, ip " << inet_ntoa(address.sin_addr) << " port " << ntohs(address.sin_port) << std::endl;

				//close the socket and mark as 0 in list for reuse
				pars.parse("QUIT :Unexpectedly left IRC", c);
				close(sd);
				sd = 0;
				_eraseClient(c);
				return ;
			}
			else
			{
				buffer[valread] = '\0';
				if (buffer[valread - 1] != '\n')
				{
					c->setBuffer(c->getBuffer() + buffer);
					return;
				}
				if (c->getBuffer().empty())
					c->setBuffer(buffer);
				else
					c->setBuffer(c->getBuffer() + buffer);
		std::cout << "buff => " << c->getBuffer() << std::endl;
				std::string command = c->getBuffer().substr(0, c->getBuffer().find(' '));
				if (c->getAccept() == true)
					pars.parse(c->getBuffer(), c);
				else
				{
					try
					{
						_checkPass(c, c->getBuffer());
					}
					catch(const std::exception& e)
					{
						send(c->getSd(), e.what(), std::strlen(e.what()), 0);
						close(sd);
						sd = 0;
						_eraseClient(c);
						return ;
					}
					
				}
				c->cleanBuffer();

				if (command == "QUIT" || command == "/quit\n" || command == "/quit")
				{
					close(sd);
					sd = 0;
					_eraseClient(c);
					return ;
				}
			}
		}
	}
}

std::vector<client *> *server::getClients()
{
	return (&clients);
}

void	server::setOffline()
{
	online = false;
}