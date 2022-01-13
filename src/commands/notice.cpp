#include "../../includes/commands/notice.hpp"

notice::notice()
{

}

notice::~notice()
{

}

void notice::execute(std::string buf, client *cli, std::vector<channel *> *channels, std::vector<client *> *cli_list)
{
	std::string notice;
	_getCmd(buf);
	channel *chan;

	if (_cmd.size() < 3)
	{
		return;
	}
	if (_cmd[1][0] == '#') /* is chan */
	{
		chan = _getChan(_cmd[1], channels);
		if (chan == NULL)
		{
			return;
		}
		if ((chan != NULL && chan->getExtMessAllow() && !chan->isMember(cli)) || (chan != NULL && chan->getModerated() && (!chan->isOp(cli) && !chan->isCanSpeakM(cli))))
		{
			return;
		}
		if (chan != NULL)
		{
			for (size_t i = 2; i < _cmd.size(); i++)
			{
				notice.append(_cmd[i]);
				if (i != _cmd.size() - 1)
					notice.append(" ");
			}
			if (notice.front() == ':')
				notice = &notice[1];
			std::string chan_message = ":" + cli->getNick() + " NOTICE " + _cmd[1] + " :" + notice + "\r\n";
			std::vector<client*> members = chan->getMembers();
			for (std::vector<client*>::iterator it = members.begin(); it != members.end(); it++)
			{
				client *c = *it;
				std::cout << "dans notice : c : " << c->getNick() << std::endl;
				if (c->getNick() != cli->getNick())
				{
					std::cout << "broadcast to : " << c->getLogin() << std::endl;
					send(c->getSd(), chan_message.c_str(), chan_message.length(), 0);
				}
			}
		}
	}
	else
	{
		std::vector<client *>::iterator it = cli_list->begin();
		client *c;
		while (it != cli_list->end())
		{
			c = *it;
			if (c->getNick() == _cmd[1])
				break;
			it++;
		}
		if (it == cli_list->end())
		{
			return;
		}
		else
		{
			std::string cli_message = ":" + cli->getNick() + " NOTICE " + _cmd[1] + " :" + _cmd[2] + "\r\n";
			send(c->getSd(), cli_message.c_str(), cli_message.length(), 0);
		}
	}
}

