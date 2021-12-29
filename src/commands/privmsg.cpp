#include "../../includes/commands/privmsg.hpp"

privmsg::privmsg()
{

}

privmsg::~privmsg()
{

}

void privmsg::execute(std::string buf, client *cli, channel *chan, client *cli_list)
{
	int i = 0;
	bool isChanExist = false;
	getCmd(buf);

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
			std::string chan_message = ":" + cli->getNick() + " PRIVMSG " + cmd[1] + " :" + cmd[2] + "\r\n";
			std::vector<client*> members = chan[i].getMembers();
			for (std::vector<client*>::iterator it = members.begin(); it != members.end(); it++)
			{
				client *c = *it;
				if (c->getNick() != cli->getNick())
				{
					//std::cout << "broadcast to : " << c->getLogin() << std::endl;
					send(c->getSd(), chan_message.c_str(), chan_message.length(), 0);
				}
			}
		}
	}
	else /* is user */
	{
		std::cout << "IS CLI !" << std::endl;
		(void)cli_list;
		int i = 0;

		while (i < 30)
		{
			if (cmd[1] == cli_list[i].getNick())
				break;
			i++;
		}
		if (i >= 30)
		{

		}
		else
		{
			std::string cli_message = ":" + cli->getNick() + " PRIVMSG " + cmd[1] + " :" + cmd[2] + "\r\n";
			send(cli_list[i].getSd(), cli_message.c_str(), cli_message.length(), 0);
		}
	}
}

void privmsg::getCmd(std::string buf)
{
	char delimiter = ' ';
	std::vector<std::string> cmd_tmp;
	std::string line;
	std::stringstream ss(buf);

	while (std::getline(ss, line, delimiter))
	{
		if (line[0] == ':')
		{
			line.append(" ");
			std::string tmp;
			while (std::getline(ss, tmp, '\n'))
				line.append(tmp);
		}
		cmd_tmp.push_back(line);
	}

	cmd.clear();
	cmd = cmd_tmp;
}