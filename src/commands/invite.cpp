#include "../../includes/commands/invite.hpp"

invite::invite()
{
}

invite::~invite()
{
}

void	invite::execute(std::string buf, client *cli, std::vector<channel *> *channels, std::vector<client *> *cli_list)
{
	std::string message;
	channel *cur_chan;

	_getCmd(buf);

	if (_cmd.size() < 3)
	{
		message = ":server " + std::string(ERR_NEEDMOREPARAMS) + " invite :Not enough parameters\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
	cur_chan = _getChan(_cmd[2], channels);
	if (cur_chan == NULL)
	{
		return;
	}
	if (!cur_chan->isOp(cli))
	{
		message = ":server " + std::string(ERR_CHANOPRIVSNEEDED) + " " + cli->getNick() + " " + cur_chan->getName() + " :You're not channel operator\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
	if (!cur_chan->isMember(cli))
	{
		message = ":server " + std::string(ERR_NOTONCHANNEL) + " " + cli->getNick() + " " + cur_chan->getName() + " :You're not on that channel\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
	if (cur_chan->isMember(_cmd[1]))
	{
		message = ":server " + std::string(ERR_USERONCHANNEL) + " " + cli->getNick() + " " + cur_chan->getName() + " :is already on channel\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
	std::vector<client *>::iterator it = cli_list->begin();
	client *c;
	bool isExist = false;
	while (it != cli_list->end())
	{
		c = *it;
		if (c->getNick() == _cmd[1])
		{
			isExist = true;
			std::cout << BOLDCYAN << " TRUE " << RESET << std::endl;
			break;
		}
		it++;
	}
	if (!isExist)
	{
		message = ":server " + std::string(ERR_NOSUCHNICK) + " " + cur_chan->getName() + " :There was no such nickname\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
	else
	{
		c->addChanInvitation(cur_chan->getName());

		message = ":" + cli->getNick() + " INVITE " + _cmd[1] + " " + _cmd[2] + "\r\n";
		send(c->getSd(), message.c_str(), message.length(), 0);

		message = ":server " + std::string(RPL_INVITING) + " nick " + c->getNick() + " " + cur_chan->getName() + "\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
	}

}
