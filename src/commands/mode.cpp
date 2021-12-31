#include "../../includes/commands/mode.hpp"

mode::mode()
{
}

mode::~mode()
{	
}

void	mode::execute(std::string buf, client *cli, std::vector<channel *> *chan)
{
	std::string message;

	_getCmd(buf);

	if (_cmd[1][0] == '#') /* is mode for chan */
	{
		channel *cur_chan = _getChan(_cmd[1], chan);
		//std::cout << BOLDRED << "cmd[2] = |" << _cmd[2] << "|" << RESET << std::endl;
		if (_cmd[3].empty())
		{
			std::cout << BOLDRED << "1" << RESET << std::endl;
			message = ":server " + std::string(RPL_CHANNELMODEIS) + " " + cur_chan->getName() + " allmode test\r\n";
			send(cli->getSd(), message.c_str(), message.length(), 0);
			return;
		}
		else if (cur_chan == NULL)
		{
			std::cout << BOLDRED << "2" << RESET << std::endl;
			message = ":server " + std::string(ERR_NOSUCHCHANNEL) + " " + cli->getNick() + " :" + _cmd[1] + " No such channel\r\n";
			send(cli->getSd(), message.c_str(), message.length(), 0);
			return;
		}
		else if (!cur_chan->isOp(cli))
		{
			std::cout << BOLDRED << "3" << RESET << std::endl;
			message = ":server " + std::string(ERR_CHANOPRIVSNEEDED) + " " + cli->getNick() + " :" + _cmd[1] + " You're not channel operator\r\n";
			send(cli->getSd(), message.c_str(), message.length(), 0);
			return;
		}
	}
	else /* is mode for cli */
	{
		std::cout << BOLDRED << "4" << RESET << std::endl;
	}
	std::cout << BOLDRED << "5" << RESET << std::endl;
}

void mode::_getCmd(std::string buf)
{
	char delimiter = ' ';
	std::vector<std::string> cmd_tmp;
	std::string line;
	std::stringstream ss(buf);

	while (std::getline(ss, line, delimiter))
	{
		std::cout << BOLDRED << "Display last char int |" << (int)line.back() << "|" << RESET << std::endl;
		if (line.back() == '\n')
		{
			line.pop_back();
			line.pop_back();
		}
		cmd_tmp.push_back(line);
	}

	_cmd.clear();
	_cmd = cmd_tmp;

	std::cout << BOLDRED << "Display spli command mode :" << RESET << std::endl;
	for (std::vector<std::string>::iterator it = _cmd.begin(); it != _cmd.end(); it++)
	{
		std::string c = *it;
		std::cout << "cmd = |" << c << "|" << std::endl;
	}
}

void mode::_o_mode_chan(client *cli, channel *chan)
{
	std::string message;

	if (_cmd[2].empty())
	{
		message = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cli->getNick() + " :Mode :Not enough parameters\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
	else if (!chan->isMember(_cmd[2]))
	{
		message = ":server " + std::string(ERR_NOSUCHNICK) + " " + _cmd[2] + " :No such nick\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
	else
	{
		if (_cmd[1][0] == '+' && !chan->isOp(chan->getCli(_cmd[2])))
			chan->addOp(chan->getCli(_cmd[2]));
		else if (_cmd[1][0] == '-' && chan->isOp(chan->getCli(_cmd[2])))
			chan->deleteOp(chan->getCli(_cmd[2]));
		message = ":server " + std::string(RPL_UMODEIS) + " " + _cmd[2] + " o chan mod set\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
}

void mode::_p_mode_chan(channel *chan)
{
	if (_cmd[1][0] == '+')
		chan->setMode('p', true);
	else if (_cmd[1][0] == '-')
		chan->setMode('p', false);
}

void mode::_s_mode_chan(channel *chan)
{
	if (_cmd[1][0] == '+')
		chan->setMode('s', true);
	else if (_cmd[1][0] == '-')
		chan->setMode('s', false);
}

void mode::_i_mode_chan(channel *chan)
{
	if (_cmd[1][0] == '+')
		chan->setMode('i', true);
	else if (_cmd[1][0] == '-')
		chan->setMode('i', false);
}

void mode::_t_mode_chan(channel *chan)
{
	if (_cmd[1][0] == '+')
		chan->setMode('t', true);
	else if (_cmd[1][0] == '-')
		chan->setMode('t', false);
}

void mode::_n_mode_chan(channel *chan)
{
	if (_cmd[1][0] == '+')
		chan->setMode('n', true);
	else if (_cmd[1][0] == '-')
		chan->setMode('n', false);
}

void mode::_m_mode_chan(channel *chan)
{
	if (_cmd[1][0] == '+')
		chan->setMode('m', true);
	else if (_cmd[1][0] == '-')
		chan->setMode('m', false);
}

void mode::_l_mode_chan(channel *chan)
{
	if (_cmd[1][0] == '+')
		chan->setMode('m', true);
	else if (_cmd[1][0] == '-')
		chan->setMode('m', false);
}

void mode::_b_mode_chan(client *cli, channel *chan)
{
	std::string message;

	if (_cmd[2].empty())
	{
		message = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cli->getNick() + " :Mode :Not enough parameters\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
	else if (!chan->isMember(_cmd[2]))
	{
		message = ":server " + std::string(ERR_NOSUCHNICK) + " " + _cmd[2] + " :No such nick\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
	else
	{
		if (_cmd[1][0] == '+' && !chan->isOp(chan->getCli(_cmd[2])))
			chan->addBan(chan->getCli(_cmd[2]));
		else if (_cmd[1][0] == '-' && chan->isOp(chan->getCli(_cmd[2])))
			chan->deleteBan(chan->getCli(_cmd[2]));
		message = ":server " + std::string(RPL_UMODEIS) + " " + _cmd[2] + " b chan mod set\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
}

void mode::_v_mode_chan(client *cli, channel *chan)
{
	std::string message;

	if (_cmd[2].empty())
	{
		message = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cli->getNick() + " :Mode :Not enough parameters\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
	else if (!chan->isMember(_cmd[2]))
	{
		message = ":server " + std::string(ERR_NOSUCHNICK) + " " + _cmd[2] + " :No such nick\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
	else
	{
		if (_cmd[1][0] == '+' && !chan->isOp(chan->getCli(_cmd[2])))
			chan->addCanSpeak(chan->getCli(_cmd[2]));
		else if (_cmd[1][0] == '-' && chan->isOp(chan->getCli(_cmd[2])))
			chan->deleteCanSpeak(chan->getCli(_cmd[2]));
		message = ":server " + std::string(RPL_UMODEIS) + " " + _cmd[2] + " v chan mod set\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
}

void mode::_k_mode_chan(std::string key, client *cli, channel *chan)
{
		std::string message;

	if (_cmd[2].empty())
	{
		message = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cli->getNick() + " :Mode :Not enough parameters\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
	else
	{
		if (_cmd[1][0] == '+')
			chan->setPassword(key);
		else if (_cmd[1][0] == '-')
			chan->setPassword("");
	}
}

void mode::_i_mode_cli(client *cli, channel *chan)
{
	std::string message;

	if (_cmd[2].empty())
	{
		message = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cli->getNick() + " :Mode :Not enough parameters\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
	else if (!chan->isMember(_cmd[2]))
	{
		message = ":server " + std::string(ERR_NOSUCHNICK) + " " + _cmd[2] + " :No such nick\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
	else
	{
		if (_cmd[1][0] == '+' && !chan->isOp(chan->getCli(_cmd[2])))
			chan->addInvisible(chan->getCli(_cmd[2]));
		else if (_cmd[1][0] == '-' && chan->isOp(chan->getCli(_cmd[2])))
			chan->deleteInvisible(chan->getCli(_cmd[2]));
		message = ":server " + std::string(RPL_UMODEIS) + " " + _cmd[2] + " i user mod set\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
}

void mode::_s_mode_cli(client *cli, channel *chan)
{
	/* to set on user maybe */
	(void)cli;
	(void)chan;
}

void mode::_w_mode_cli(client *cli, channel *chan)
{
	/*Pas sur de comprendre*/
	(void)cli;
	(void)chan;
}

void mode::_o_mode_cli(client *cli, channel *chan)
{
	/* IRC-operator status, can only be set by IRC-ops with OPER */
	(void)cli;
	(void)chan;
}