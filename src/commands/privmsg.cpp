#include "../../includes/commands/privmsg.hpp"

privmsg::privmsg()
{
}

privmsg::~privmsg()
{
}

void privmsg::execute(std::string buf, client *cli, std::vector<channel *> *channels, std::vector<client *> *cli_list)
{
	std::string message;
	std::string privmsg;
	_getCmd(buf);
	channel *chan;

	if (_cmd.size() < 3)
	{
		message = ":server " + std::string(ERR_NOTEXTTOSEND) + " " + cli->getNick() + " :No text to send\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
	if (_cmd[1][0] == '#') /* is chan */
	{
		chan = _getChan(_cmd[1], channels);
		if (chan == NULL)
		{
			message = ":server " + std::string(ERR_NOSUCHCHANNEL) + " " + cli->getNick() + " " + _cmd[1] + " :No such channel\r\n";
			send(cli->getSd(), message.c_str(), message.length(), 0);
			return;
		}
		if ((chan != NULL && chan->getExtMessAllow() && !chan->isMember(cli)) || (chan != NULL && chan->getModerated() && (!chan->isOp(cli) && !chan->isCanSpeakM(cli))))
		{
			message = ":server " + std::string(ERR_CANNOTSENDTOCHAN) + " " + cli->getNick() + " " + _cmd[1] + " :Cannot send to channel\r\n";
			send(cli->getSd(), message.c_str(), message.length(), 0);
			return;
		}
		if (chan != NULL)
		{
			for (size_t i = 2; i < _cmd.size(); i++)
			{
				privmsg.append(_cmd[i]);
				if (i != _cmd.size() - 1)
					privmsg.append(" ");
			}
			if (privmsg.front() == ':')
				privmsg = &privmsg[1];
			std::string chan_message = ":" + cli->getNick() + " PRIVMSG " + _cmd[1] + " :" + privmsg + "\r\n";
			std::vector<client*> members = chan->getMembers();
			for (std::vector<client*>::iterator it = members.begin(); it != members.end(); it++)
			{
				client *c = *it;
				if (c->getNick() != cli->getNick())
					send(c->getSd(), chan_message.c_str(), chan_message.length(), 0);
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
			std::string tmp = ":server " + std::string(ERR_NOSUCHNICK) + " " + _cmd[1] + " :No such nick\r\n";
			send(cli->getSd(), tmp.c_str(), tmp.length(), 0);
			return;
		}
		else
		{
			for (size_t i = 2; i < _cmd.size(); i++)
			{
				privmsg.append(_cmd[i]);
				if (i != _cmd.size() - 1)
					privmsg.append(" ");
			}
			if (privmsg.front() == ':')
				privmsg = &privmsg[1];
			std::string cli_message = ":" + cli->getNick() + " PRIVMSG " + _cmd[1] + " :" + privmsg + "\r\n";
			send(c->getSd(), cli_message.c_str(), cli_message.length(), 0);
		}
	}
}

