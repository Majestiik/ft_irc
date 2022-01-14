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
	if (_cmd.size() == 3)
	{

	}

	channel *cur_chan = _getChan(_cmd[1], channels);

	if (_cmd.size() > 3 && _cmd[3] == "TALK")
	{
		_talk(cli, cur_chan);
	}
}

void bot::_talk(client *cli, channel *chan)
{
	std::string chan_message;
	if (_cmd.size() == 4)
	{
		chan_message = ":" + getName() + " PRIVMSG " + _cmd[1] + " : Oui, que veux tu " + cli->getNick() + " ? Comment oses tu me reveiller de ma sieste !\r\n";
	}
	else if (_cmd.size() > 4 && _cmd[4] == "hello")
	{
		chan_message = ":" + getName() + " PRIVMSG " + _cmd[1] + " : Tout vas bien et toi BG du 69 ?\r\n";
	}
	else if (_cmd.size() > 4)
	{
		chan_message = ":" + getName() + " PRIVMSG " + _cmd[1] + " : Quoi ? rien compris moi ...\r\n";
	}
	std::vector<client*> members = chan->getMembers();
	for (std::vector<client*>::iterator it = members.begin(); it != members.end(); it++)
	{
		client *c = *it;
		send(c->getSd(), chan_message.c_str(), chan_message.length(), 0);
	}
}