//Example code: A simple server side code, which echos back the received message.
//Handle multiple socket connections with select and fd_set on Linux 
#include <stdio.h> 
#include <string.h>   //strlen 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>   //close 
#include <arpa/inet.h>    //close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros 
#include <iostream>

#define TRUE 1
#define FALSE 0
#define PORT 8080

int	main(int ac, char** av)
{
	bool opt = TRUE;
	int masterSocket, addrlen, newSocket, clientSocket[30], max_clients = 30, activity, i, valread, sd;
	int max_sd;
	struct sockaddr_in address;

	char buffer[1024];

	//set df socket descriptors
	fd_set readfds;

	//initialise all clientSocket[] to 0 so not checked
	std::string message = "Bonjour \r\n";
	for (i = 0; i < max_clients; i++)
		clientSocket[i] = 0;

	//create a master socket
	if ( (masterSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("Socket failed");
		exit(EXIT_FAILURE);
	}

	//set master socket to allow multiple connections
	/* if( setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 ) 
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}*/

	//type of socket created
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	//bind the socket to localhost port 8080
	if (bind(masterSocket, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	std::cout << "listener on port " << PORT << std::endl;

	//try to specify maximum of 3 pending connections for the master socket
	if (listen(masterSocket, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	//accept the incoming connection
	addrlen = sizeof(address);
	std::cout << "waiting for connections..." << std::endl;

	while(TRUE)
	{
		//cleear the socket set
		FD_ZERO(&readfds);

		//add master socket to set
		FD_SET(masterSocket, &readfds);
		max_sd = masterSocket;

		//add child sockets to set
		for (i = 0; i < max_clients; i++)
		{
			//socket descriptor
			sd = clientSocket[i];

			//if valid socket descriptor then aff to read list
			if (sd > 0)
				FD_SET(sd, &readfds);
			
			//highest file descriptor number, need it for the select function
			if (sd > max_sd)
				max_sd = sd;
		}

		//wait for an activity on one of the socketsm timeout is NULL
		//so wait indefinitely
		activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

		if ((activity < 0) && (errno!=EINTR))
			std::cout << "select error" << std::endl;
	
		//if something happens on the master socket,
		//then it's an incoming connexion
		if (FD_ISSET(masterSocket, &readfds))
		{
			if ((newSocket = accept(masterSocket, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
			{
				perror("accept");
				exit(EXIT_FAILURE);
			}

			//inform user f socket number - used in send and receive commands
			std::cout << "New connection, socket fd is " << newSocket << " ip is " << inet_ntoa(address.sin_addr) << " port : " << ntohs(address.sin_port) << std::endl;

			//send new connection greeting message
			if (send(newSocket, message.c_str(), message.length(), 0) != message.length())
			{
				perror("send");
			}
			std::cout << "Welcome message sent successfully" << std::endl;

			//add new socket to array of sockets
			for (i = 0; i < max_clients; i++)
			{
				if (clientSocket[i] == 0)
				{
					clientSocket[i] = newSocket;
					std::cout << "Adding to list of sockets as " << i << std::endl;

					break ;
				}
			}
		}

		//else its some IO operation one some other socket
		for (i = 0; i < max_clients; i++)
		{
			sd = clientSocket[i];

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
					clientSocket[i] = 0;
				}
				//Echo back the message that came in
				else
				{
					//set the string terminating NULL byte on the end of the data read
					buffer[valread] = '\0';
					send(sd, buffer, strlen(buffer), 0);
					std::cout << "===BUFFER : " << buffer << std::endl;
				}
			}
		}
	}
	return 0;

}