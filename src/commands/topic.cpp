#include "../../includes/commands/topic.hpp"

topic::topic()
{
}

topic::~topic()
{
}

void topic::execute(std::string buf, client *cli, std::vector<channel *> *channels)
{
	std::string message;
	channel *cur_chan;

	getCmd(buf);


	std::cout << BOLDYELLOW << "_cmd.size() = " << _cmd.size() << RESET << std::endl;

	if (_cmd.size() < 2)
	{
		message = ":server " + std::string(ERR_NEEDMOREPARAMS) + " topic :Not enough parameters\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
	cur_chan = _getChan(_cmd[1], channels);
	if (cur_chan != NULL)
	{
		if (!cur_chan->isMember(cli))
		{
			message = ":server " + std::string(ERR_NOTONCHANNEL) + " " + cli->getNick() + " " + cur_chan->getName() + " :You're not on that channel\r\n";
			send(cli->getSd(), message.c_str(), message.length(), 0);
			return;
		}
		else if (_cmd.size() == 2)
		{
			message = ":server " + std::string(RPL_TOPIC) + " " + cli->getNick() + " " + cur_chan->getName() + " :" + cur_chan->getTopic() + "\r\n";
			send(cli->getSd(), message.c_str(), message.length(), 0);
		}
		else if (!cur_chan->isOp(cli))
		{
			message = ":server " + std::string(ERR_CHANOPRIVSNEEDED) + " " + cli->getNick() + " " + cur_chan->getName() + " :You're not channel operator\r\n";
			send(cli->getSd(), message.c_str(), message.length(), 0);
			return;
		}
		else
		{
			cur_chan->setTopic(_cmd[2]);
		}
	}
}

void topic::getCmd(std::string buf)
{
	char delimiter = ' ';
	int i = 0;
	std::vector<std::string> cmd_tmp;
	std::string line;
	std::stringstream ss(buf);

	while (std::getline(ss, line, delimiter))
	{
		cmd_tmp.push_back(line);
		i++;
		if (i == 2)
			delimiter = '\n';
	}

	while (cmd_tmp.back().back() == '\n' || cmd_tmp.back().back() == '\r')
		cmd_tmp.back().pop_back();

	for (std::vector<std::string>::iterator it = cmd_tmp.begin(); it != cmd_tmp.end(); it++)
	{
			std::cout << BOLDYELLOW << "_cmd = |" << *it << "|" << RESET << std::endl;
	}
	

	_cmd.clear();
	if (cmd_tmp[1] == ":")
		cmd_tmp.pop_back();
	_cmd = cmd_tmp;
}
