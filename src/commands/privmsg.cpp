#include "../../includes/commands/privmsg.hpp"

privmsg::privmsg()
{

}

privmsg::~privmsg()
{

}

void privmsg::execute(std::string buf, client *cli, channel *chan)
{
	int i = 0;
	bool isChanExist = false;
	getCmd(buf);

	std::cout << "buf dans privmsg : " << buf << std::endl;
	std::cout << "cli de privmsg : " << cli->getLogin() << std::endl;
	std::cout << "cmd[1] : " << cmd[1] << std::endl;


	/* Sends <message> to <msgtarget>, which is usually a user or channel. */
	if (cmd[1][0] == '#') /* is chan */
	{
		std::cout << "IS CHAN !" << std::endl;
		for (i = 0; chan[i].getExists() == true; i++)
		{
			if (chan[i].getName() == cmd[1])
			{
				isChanExist = true;
				break;
			}
		}
		if (isChanExist)
		{
			std::string message = ":" + cli->getNick() + " PRIVMSG " + cmd[1] + " :" + cmd[2] + "\r\n";
			std::vector<client*> members = chan[i].getMembers();
			for (std::vector<client*>::iterator it = members.begin(); it != members.end(); it++)
			{
				client *c = *it;
				if (c->getNick() != cli->getNick())
				{
					std::cout << "broadcast to : " << c->getLogin() << std::endl;
					send(c->getSd(), message.c_str(), message.length(), 0);
				}
			}
		}
	}
	else /* is user */
	{
		std::cout << "IS CLI !" << std::endl;
		/*client target =  need to get list of ALL client */
	}
}

void privmsg::getCmd(std::string buf) /*Generic function for all command (move to command class later)*/
{
	std::string tmp;
	int i_tmp = 0;

	for (size_t i = 0; buf[i] != '\r' && buf[i] != '\n'; i++)
	{
		if (buf[i] != ' ' && buf[i] != '\n' && buf[i] != '\r')
		{
			tmp[i_tmp] = buf[i];
			std::cout << "tmp[" << i_tmp << "] " << tmp[i_tmp] << std::endl;
			i_tmp++;
		}
		else if (buf[i] == ' ')
		{
			//std::cout << "insert " << i << std::endl;
			cmd.push_back(tmp);
			//std::cout << "tmp clear " << i << std::endl;
			tmp.clear();
			i_tmp = 0;
			//std::cout << "while skip space " << i << std::endl;
			while (buf[i] && buf[i] == ' ')
				i++;
		}
	}
	std::vector<std::string>::iterator it = cmd.begin();
	while (it != cmd.end())
	{
		std::cout << "cmd = " << (*it).front() << std::endl;
		it++;
	}
	
}