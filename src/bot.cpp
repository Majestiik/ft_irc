#include "../includes/bot.hpp"

bot::bot()
{
	_name = "BotteurDeFesse";
	_isActive = true;
}

bot::~bot()
{
}
		
std::string	bot::getName() const
{
	return _name;
}

bool	bot::getIsActive() const
{
	return _isActive;
}

bool	bot::getIsBanWActive() const
{
	return _isBanWActive;
}

std::string	bot::getBanWords() const
{
	std::string banWlist;
	for (std::vector<std::string>::const_iterator it = _banWordsList.begin(); it != _banWordsList.end(); it++)
	{
		banWlist.append((*it));
		if (it + 1 != _banWordsList.end())
			banWlist.append(", ");
	}
	return banWlist;
}

void	bot::setName(std::string name)
{
	_name = name + "_BOT_";
}

void	bot::setActive(bool state)
{
	_isActive = state;
}

void	bot::setBanWActive(bool state)
{
	_isBanWActive = state;
}

void	bot::addBanWord(std::string banWord)
{
	_banWordsList.push_back(banWord);
}

int	bot::delBanWord(std::string banWord)
{
	for (std::vector<std::string>::const_iterator it = _banWordsList.begin(); it != _banWordsList.end(); it++)
	{
		if ((*it) == banWord)
		{
			_banWordsList.erase(it);
			return 1;
		}
	}
	return 0;
}

bool	bot::isBanWorld(std::string message)
{
	for (std::vector<std::string>::iterator it = _banWordsList.begin(); it != _banWordsList.end(); it++)
	{
		if (message.find((*it)) != std::string::npos)
			return true;
	}
	return false;
}

bool	bot::execute(std::vector<std::string> _cmd, std::string cli_name, int cli_sd, bool cliIsOpe, std::string chan, std::vector<client*> members)
{
	//std::cout << BOLDMAGENTA << "command = |" << _cmd[2] + " " + _cmd[3] << "|" << RESET << std::endl;
	if (getIsActive())
	{
		if (_cmd.size() > 2 && (_cmd[2] == "!TALK" || _cmd[2] == "!talk"))
		{
			_talk(_cmd, cli_name, cli_sd, chan);
			return (true);
		}

		if (_cmd.size() > 2 && (_cmd[2] == "!HELP" || _cmd[2] == "!help"))
		{
			_help(_cmd, cli_name, cli_sd, cliIsOpe, chan);
			return (true);
		}

		if (_cmd.size() > 2 && (_cmd[2] == "!BANWORDS" || _cmd[2] == "!banwords"))
		{
			_banWords(_cmd, cli_name, cli_sd, cliIsOpe, chan);
			return (true);
		}

		if (_cmd.size() > 2 && (_cmd[2] == "!OFF" || _cmd[2] == "!off") && cliIsOpe)
		{
			_off(members, chan);
			return (true);
		}
	}
	else
	{
		if (_cmd.size() > 2 && (_cmd[2] == "!ON" || _cmd[2] == "!on") && cliIsOpe)
		{
			_on(members, chan);
			return (true);
		}
	}
	return (false);
}

void	bot::welcomeMsg(std::string cli_name, std::string chan, std::vector<client*> members)
{
	std::string message;
	int r = rand() % 5 + 1;

	if (r == 1)
		message = ":" + getName() + " PRIVMSG " + chan + " : Say hello to " + cli_name + ", and be nice to his !\r\n";
	else if (r == 2)
		message = ":" + getName() + " PRIVMSG " + chan + " : " + cli_name + " just arrived, he's bright !\r\n";
	else if (r == 3)
		message = ":" + getName() + " PRIVMSG " + chan + " : A wild " + cli_name + " just appeared, he looks uncapturable..\r\n";
	else if (r == 4)
		message = ":" + getName() + " PRIVMSG " + chan + " : What a racket, we heard " + cli_name + " arrive at 10 miles around\r\n";
	else if (r == 5)
		message = ":" + getName() + " PRIVMSG " + chan + " : We've been waiting for it and here it is! " + cli_name + " the handsome guy\r\n";

	for (std::vector<client*>::iterator it = members.begin(); it != members.end(); it++)
	{
		client *c = *it;
		send(c->getSd(), message.c_str(), message.length(), 0);
	}
}

void	bot::_talk(std::vector<std::string> _cmd, std::string cli_name, int cli_sd, std::string chan)
{
	std::string chan_message;
	if (_cmd.size() == 3)
	{
		chan_message = ":" + getName() + " PRIVMSG " + chan + " : Yes ?? " + cli_name + " ? I hope it's important , you leave me to my bed\r\n";
	}
	else if (_cmd.size() > 3 && _cmd[3] == "hello")
	{
		chan_message = ":" + getName() + " PRIVMSG " + chan + " : Hii ! How are you today " + cli_name + " ?\r\n";
	}
	else if (_cmd.size() > 3)
	{
		chan_message = ":" + getName() + " PRIVMSG " + chan + " : What are you saying ? i'm understand nothing...\r\n";
	}

	/* Send only to emmiter client */
	send(cli_sd, chan_message.c_str(), chan_message.length(), 0);

	/* Send to all client */
	/*std::vector<client*> members = chan->getMembers();
	for (std::vector<client*>::iterator it = members.begin(); it != members.end(); it++)
	{
		client *c = *it;
		send(c->getSd(), chan_message.c_str(), chan_message.length(), 0);
	}*/
}

void	bot::_help(std::vector<std::string> _cmd, std::string cli_name, int cli_sd, bool cliIsOpe, std::string chan)
{
	(void) chan;
	std::string chan_message;
	if (_cmd.size() == 3 && cliIsOpe)
	{
		chan_message = ":" + getName() + " PRIVMSG " + _cmd[1] + " : Here are the commands available for you " + cli_name + " :\r\n";
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :                           Official IRC commands\r\n";	
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /topic <new topic>                    to change the topic of the channel, type only /topic for see the topic\r\n";	
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /mode +?                              for see the channel's active mode, for change mode utilisation, type !help mode\r\n";	
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /names <channel> <channel> ...        for see the names of user in channels (if no channel give, see in all visible channels)\r\n";
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /invite <nickname> <channel>          for send channel invitation to user\r\n";
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /kick <nickname> <reason>             for kick user to channel, reason is facultative\r\n";
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /privmsg <nickname> <text>            for send a private message to user\r\n";
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /notice <nickname> <text>             like privmsg but without error reply\r\n";
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /part <reason>                        for leave the channel, reason is facultative\r\n";
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /nick <new nickname>                  for change your nickname\r\n";
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /list                                 for see the list of visible channels\r\n";
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /join <channel>                       for enter in a channel, if do not exist, create new one with you as operator\r\n";
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /quit <reason>                        for leave the server, reason is facultative\r\n";
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);

		chan_message = ":---> PRIVMSG " + _cmd[1] + " :                           Bot commands\r\n";	
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     !on                                   to enable the BOT\r\n";	
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     !off                                  to disable the BOT\r\n";	
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     !help                                 to see this message\r\n";	
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     !talk <text>                          to try to speak with the BOT, try to write hello for exemple\r\n";	
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     !banwords                             to see if banwords function is activated on this channel , and see the list of ban words\r\n";	
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     !banwords on                          to enabled a ban words function\r\n";	
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     !banwords off                         to disable a ban words function\r\n";	
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     !banwords add                         to add a ban word\r\n";	
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     !banwords del                         to delete a ban word\r\n";	
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);

	}
	if (_cmd.size() == 3 && !cliIsOpe)
	{
		chan_message = ":" + getName() + " PRIVMSG " + _cmd[1] + " : Here are the commands available for you " + cli_name + " :\r\n";
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :                           Official IRC commands\r\n";	
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /topic                                for see the topic\r\n";	
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /mode +?                              for see the channel's active mode\r\n";	
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /names <channel> <channel> ...        for see the names of user in channels (if no channel give, see in all visible channels)\r\n";
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /invite <nickname> <channel>          for send channel invitation to user\r\n";
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /privmsg <nickname> <text>            for send a private message to user\r\n";
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /notice <nickname> <text>             like privmsg but without error reply\r\n";
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /part <reason>                        for leave the channel, reason is facultative\r\n";
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /nick <new nickname>                  for change your nickname\r\n";
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /list                                 for see the list of visible channels\r\n";
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /join <channel>                       for enter in a channel, if do not exist, create new one with you as operator\r\n";
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     /quit <reason>                        for leave the server, reason is facultative\r\n";
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);

		chan_message = ":---> PRIVMSG " + _cmd[1] + " :                           Bot commands\r\n";	
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     !help                                 to see this message\r\n";	
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     !talk <text>                          to try to speak with the BOT, try to write hello for exemple\r\n";	
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
		chan_message = ":---> PRIVMSG " + _cmd[1] + " :     !banwords                             to see if banwords function is activated on this channel , and see the list of ban words\r\n";	
		send(cli_sd, chan_message.c_str(), chan_message.length(), 0);
	}
}

void	bot::_on(std::vector<client*> members, std::string chan)
{
	std::string message;
	message = ":" + getName() + "!" + getName() + "@0.0.0.0 JOIN " + chan + " :" + "is off"+ "\r\n";
	for (std::vector<client*>::iterator it = members.begin(); it != members.end(); it++)
		send((*it)->getSd(), message.c_str(), message.length(), 0);
	setActive(true);
}

void	bot::_off(std::vector<client*> members, std::string chan)
{
	std::string message;
	message = ":" + getName() + "!" + getName() + "@0.0.0.0 PART " + chan + " :" + "is off"+ "\r\n";
	for (std::vector<client*>::iterator it = members.begin(); it != members.end(); it++)
		send((*it)->getSd(), message.c_str(), message.length(), 0);
	setActive(false);
}

void	bot::_banWOn(int cli_sd, std::string chan)
{
	std::string message;
	message = ":" + getName() + " PRIVMSG " + chan + " : Activation of the banned word function\r\n";
	send(cli_sd, message.c_str(), message.length(), 0);
	setBanWActive(true);
}

void	bot::_banWOff(int cli_sd, std::string chan)
{
	std::string message;
	message = ":" + getName() + " PRIVMSG " + chan + " : Disabling the banned word function\r\n";
	send(cli_sd, message.c_str(), message.length(), 0);
	setBanWActive(false);
}

void	bot::_banWords(std::vector<std::string> _cmd, std::string cli, int cli_sd, bool cliIsOpe, std::string chan)
{
	(void)cli;
	std::string message;

	if (_cmd.size() == 3)
	{
		message = ":" + getName() + " PRIVMSG " + chan + " : The ban words function is " + ((getIsBanWActive() == true) ? "enable" : "disable") + " on this channel\r\n";
		send(cli_sd, message.c_str(), message.length(), 0);
		if (_banWordsList.size() == 0)
			message = ":---> PRIVMSG " + chan + " : The list of banned words is empty\r\n";
		else
			message = ":---> PRIVMSG " + chan + " : Here are the list of banned words on this channel : " + getBanWords() + "\r\n";
		send(cli_sd, message.c_str(), message.length(), 0);	
	}
	else if (_cmd.size() > 4 && _cmd[3] == "add" && cliIsOpe)
	{
		addBanWord(_cmd[4]);
		message = ":" + getName() + " PRIVMSG " + chan + " : The word banned has been added\r\n";
		send(cli_sd, message.c_str(), message.length(), 0);
	}
	else if (_cmd.size() > 4 && _cmd[3] == "del" && cliIsOpe)
	{
		if (delBanWord(_cmd[4]) == 1)
		{
			message = ":" + getName() + " PRIVMSG " + chan + " : The banned word has been removed\r\n";
			send(cli_sd, message.c_str(), message.length(), 0);
		}
	}
	else if (_cmd.size() > 3 && _cmd[3] == "on" && !getIsBanWActive() && cliIsOpe)
		_banWOn(cli_sd, chan);
	else if (_cmd.size() > 3 && _cmd[3] == "off" && getIsBanWActive() && cliIsOpe)
		_banWOff(cli_sd, chan);
}