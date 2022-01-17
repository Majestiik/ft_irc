#include "../includes/bot.hpp"

bot::bot()
{
	_name = "_BOT_";
}

bot::~bot()
{
}
		
std::string	bot::getName() const
{
	return _name;
}

void		bot::setName(std::string name)
{
	_name = name + "_BOT_";
}

void	bot::execute(std::string buf, client *cli, std::vector<channel *> *channels)
{
	(void)cli;
	_getCmd(buf);

	std::cout << BOLDMAGENTA << "command = |" << _cmd[2] + " " + _cmd[3] << "|" << RESET << std::endl;

	channel *cur_chan = _getChan(_cmd[1], channels);

	if (_cmd.size() > 2 && (_cmd[2] == "!TALK" || _cmd[2] == "!talk"))
	{
		_talk(cli, cur_chan);
	}

	if (_cmd.size() > 2 && (_cmd[2] == "!HELP" || _cmd[2] == "!help"))
	{
		_help(cli, cur_chan);
	}
}

void bot::_talk(client *cli, channel *chan)
{
	(void)chan;
	std::string chan_message;
	if (_cmd.size() == 3)
	{
		chan_message = ":" + getName() + " PRIVMSG " + _cmd[1] + " : Oui, que veux tu " + cli->getNick() + " ? Comment oses tu me reveiller de ma sieste !\r\n";
	}
	else if (_cmd.size() > 3 && _cmd[4] == "hello")
	{
		chan_message = ":" + getName() + " PRIVMSG " + _cmd[1] + " : Tout vas bien et toi BG du 69 ?\r\n";
	}
	else if (_cmd.size() > 3)
	{
		chan_message = ":" + getName() + " PRIVMSG " + _cmd[1] + " : Quoi ? rien compris moi ...\r\n";
	}

	/* Send only to emmiter client */
	send(cli->getSd(), chan_message.c_str(), chan_message.length(), 0);

	/* Send to all client */
	/*std::vector<client*> members = chan->getMembers();
	for (std::vector<client*>::iterator it = members.begin(); it != members.end(); it++)
	{
		client *c = *it;
		send(c->getSd(), chan_message.c_str(), chan_message.length(), 0);
	}*/
}

void bot::_help(client *cli, channel *chan)
{
	(void)chan;
	std::string chan_message;
	if (_cmd.size() == 3)
	{
		chan_message = ":" + getName() + " PRIVMSG " + _cmd[1] + " : Voici les commandes disponible pour toi " + cli->getNick() + " :\r\n";
		send(cli->getSd(), chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /topic <new topic>                    for change the channel's topic, type only /topic for see the channel's topic\r\n";	
		send(cli->getSd(), chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /mode +?                              for see the channel's active mode, for change mode utilisation, type !help mode\r\n";	
		send(cli->getSd(), chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /names <channel> <channel> ...        for see the names of user in channels (if no channel give, see in all visible channels)\r\n";
		send(cli->getSd(), chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /invite <nickname> <channel>          for send channel invitation to user\r\n";
		send(cli->getSd(), chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /kick <nickname> <reason>             for kick user to channel, reason is facultative\r\n";
		send(cli->getSd(), chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /privmsg <nickname> <text>            for send a private message to user\r\n";
		send(cli->getSd(), chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /notice <nickname> <text>             like privmsg but without error reply\r\n";
		send(cli->getSd(), chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /part <reason>                        for leave the channel, reason is facultative\r\n";
		send(cli->getSd(), chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /nick <new nickname>                  for change your nickname\r\n";
		send(cli->getSd(), chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /list                                 for see the list of visible channels\r\n";
		send(cli->getSd(), chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /join <channel>                       for enter in a channel, if do not exist, create new one with you as operator\r\n";
		send(cli->getSd(), chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /quit <reason>                        for leave the server, reason is facultative\r\n";
		send(cli->getSd(), chan_message.c_str(), chan_message.length(), 0);
		/*chan_message = ":server " + std::string(RPL_MYINFO) + " " + _cmd[1] + " :Test Info\r\n";
		send(cli->getSd(), chan_message.c_str(), chan_message.length(), 0);

		chan_message = ":server " + std::string(RPL_MOTDSTART) + " " + _cmd[1] + " :- <server> Message of the day - \r\n";
		send(cli->getSd(), chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":server " + std::string(RPL_MOTD) + " " + _cmd[1] + " :- truck de fou\r\n";
		send(cli->getSd(), chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":server " + std::string(RPL_ENDOFINFO) + " " + _cmd[1] + " :End of MOTD command\r\n";
		send(cli->getSd(), chan_message.c_str(), chan_message.length(), 0);*/

	}
	/*else if (_cmd.size() > 3 && _cmd[4] == "hello")
	{
		chan_message = ":" + getName() + " PRIVMSG " + _cmd[1] + " : Tout vas bien et toi BG du 69 ?\r\n";
	}
	else if (_cmd.size() > 3)
	{
		chan_message = ":" + getName() + " PRIVMSG " + _cmd[1] + " : Quoi ? rien compris moi ...\r\n";
	}*/

	/* Send only to emmiter client */
	//send(cli->getSd(), chan_message.c_str(), chan_message.length(), 0);

	/* Send to all client */
	/*std::vector<client*> members = chan->getMembers();
	for (std::vector<client*>::iterator it = members.begin(); it != members.end(); it++)
	{
		client *c = *it;
		send(c->getSd(), chan_message.c_str(), chan_message.length(), 0);
	}*/
}