#include "../includes/parser.hpp"

parser::parser()
{
}

parser::~parser()
{
}


void	parser::parse(std::string buf, client *cli, channel *channels)
{
	//std::string buf = buffer;
	int space = buf.find(' ');
	(void)cli;
	std::cout << "space : " << space << std::endl;
	std::string command = buf.substr(0, space);
	std::cout << "command : " << command << std::endl;
	
	if (command == "NICK")
	{
		std::cout << "buf.length : " << buf.length() << std::endl;
		buf = buf.substr(space + 1, buf.length() - space - 1);
		space = buf.find('U');
		std::cout << "== buf avant setNick() : " << buf << std::endl;
		if (space > 0)
		{
			cli->setNick(buf.substr(0, space - 1));
			buf = buf.substr(space, buf.length() - space);
			command = "USER";
			space = buf.find(' ');
		}
		else
			cli->setNick(buf.substr(0, buf.length() - 2));
		std::cout << "buf apres setnick : " << buf << " et nick : " << cli->getNick() << std::endl;
	}
		
	if (command == "USER")
	{
		buf = buf.substr(space + 1, buf.length() - (space + 3));
		space = buf.find(' ');
		cli->setLogin(buf.substr(0, space));
		space = buf.find(':');
		if (space < 0)
			space = buf.find('*') + 1;
		buf = buf.substr(space + 1, buf.length() - (space + 1));
		cli->setRealName(buf);
		std::string message = ":127.0.0.1 001 " + cli->getNick() + " :Welcome to the IRMEGASTONKS network, you'll see it's incredible\r\n";
		if (send(cli->getSd(), message.c_str(), message.length(), 0) != (long)message.length())
			std::cerr << "send" << std::endl;
		else
			std::cout << "Welcome message sent successfully" << std::endl;
	}

	if (command == "JOIN")
	{

		//join j(name, cli, serv);
		buf = buf.substr(space + 1, buf.length() - (space + 3));
		_join.execute(buf, cli, channels);
		
		/*std::cout << "channel name : " << buf << std::endl;
		int i = 0;
		while (channels[i].getExists() == true)
			i++;
		channels[i].setName(buf);
		channels[i].setExists(true);
		channels[i].addClient(cli);
		channels[i].create();

		std::string message = ":" + cli->getNick() + "!" + cli->getLogin() + "@" + "127.0.0.1" + " JOIN " + buf;
		std::cout << "message : " << message << std::endl;
		send(cli->getSd(), message.c_str(), message.length(), 0);*/
	}

	if (command == "PRIVMSG")
	{

	}

	if (command == "PART")
	{
		buf = buf.substr(space + 1, buf.length() - (space + 3));
		_part.execute(buf, cli, channels);
	}

	if (command == "EXIT")
		std::exit(0);

	if (command == "QUIT")
		_quit.execute(buf, cli, channels);
	
}
//(":" + user->getNickName() + "!" + user->getUserName() + "@" + user->getAddress() + " JOIN " + _channelName);

void	parser::setServ(server *serv)
{
	_serv = serv;
}