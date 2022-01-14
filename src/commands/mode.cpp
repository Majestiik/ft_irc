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
	std::string mode = "opsitnmlbvk";
	size_t i = 1;

	_getCmd(buf);

	if (_cmd.size() > 1 && _cmd[1][0] == '#') /* is mode for chan */
	{
		channel *cur_chan = _getChan(_cmd[1], chan);
		if (cur_chan == NULL)
		{
			message = ":server " + std::string(ERR_NOSUCHCHANNEL) + " " + cli->getNick() + " " + _cmd[1] + " :No such channel\r\n";
			send(cli->getSd(), message.c_str(), message.length(), 0);
			return;
		}
		if (_cmd.size() == 2)
		{
			message = ":server " + std::string(RPL_CHANNELMODEIS) + " " + cli->getNick() + " " + cur_chan->getName() + " :" + cur_chan->getAllCurrentModes() + "\r\n";
			send(cli->getSd(), message.c_str(), message.length(), 0);
			return;
		}
		if (!cur_chan->isOp(cli))
		{
			message = ":server " + std::string(ERR_CHANOPRIVSNEEDED) + " " + cli->getNick() + " " + cur_chan->getName() + " :You're not channel operator\r\n";
			send(cli->getSd(), message.c_str(), message.length(), 0);
			return;
		}
		if (_cmd.size() > 2 && mode.find(_cmd[2][1]) == std::string::npos)
		{
			message = ":server " + std::string(ERR_UNKNOWNMODE) + " " + _cmd[2][1] + " :is unknown mode char\r\n";
			send(cli->getSd(), message.c_str(), message.length(), 0);
			return;
		}
		if (_cmd.size() > 2)
		{
			while (_cmd[2].size() > i)
			{
				if (_cmd[2][i] == 'o')
					_o_mode_chan(cli, cur_chan);
				else if (_cmd[2][i] == 'p')
					_p_mode_chan(cli, cur_chan);
				else if (_cmd[2][i] == 's')
					_s_mode_chan(cli, cur_chan);
				else if (_cmd[2][i] == 'i')
					_i_mode_chan(cli, cur_chan);
				else if (_cmd[2][i] == 't')
					_t_mode_chan(cli, cur_chan);
				else if (_cmd[2][i] == 'n')
					_n_mode_chan(cli, cur_chan);
				else if (_cmd[2][i] == 'm')
					_m_mode_chan(cli, cur_chan);
				else if (_cmd[2][i] == 'l')
					_l_mode_chan(cli, cur_chan);
				else if(_cmd[2][i] == 'b')
					_b_mode_chan(cli, cur_chan);
				else if(_cmd[2][i] == 'v')
					_v_mode_chan(cli, cur_chan);
				else if(_cmd[2][i] == 'k')
					_k_mode_chan(cli, cur_chan);
				i++;
			}
		}
	}
	else if (_cmd.size() > 1)
		return ;
	else
	{
		message = ":server " + std::string(ERR_NEEDMOREPARAMS) + " Mode :Not enough parameters\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
}

void mode::_inform_mode_change(std::string mode, client *cli, channel *chan)
{
	std::string message;
	std::vector<client *> cli_list = chan->getMembers();

	for (std::vector<client *>::iterator it = cli_list.begin(); it != cli_list.end(); it++)
	{
		message = ":server " + std::string(RPL_CHANNELMODEIS) + " " + cli->getNick() + " " + chan->getName() + " :" + cli->getNick() +  " use " + mode + "\r\n";
		send((*it)->getSd(), message.c_str(), message.length(), 0);
	}
}

void mode::_o_mode_chan(client *cli, channel *chan)
{
	std::string message;
	client *target_cli;
	std::vector<client *> cli_list;

	if (_cmd[3].empty())
	{
		message = ":server " + std::string(ERR_NEEDMOREPARAMS) + " Mode :Not enough parameters\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
	else if (!chan->isMember(_cmd[3]))
	{
		message = ":server " + std::string(ERR_NOSUCHNICK) + " " + _cmd[3] + " :No such nick\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
	else
	{
		target_cli = chan->getCli(_cmd[3]);
		cli_list = chan->getMembers();
		if (_cmd[2][0] == '+' && !chan->isOp(chan->getCli(_cmd[3])))
		{
			chan->addOp(target_cli);
			_inform_mode_change( "+o on " + target_cli->getNick(), cli, chan);
		}
		else if (_cmd[2][0] == '-' && chan->isOp(chan->getCli(_cmd[3])))
		{
			chan->deleteOp(target_cli);
			_inform_mode_change( "-o on " + target_cli->getNick(), cli, chan);
		}
		for (std::vector<client *>::iterator it = cli_list.begin(); it != cli_list.end(); it++)
		{
			message = ":server " + std::string(RPL_NAMREPLY) + " " + (*it)->getNick() + " = " + chan->getName() + " :" + chan->listClients() + "\r\n";
			send((*it)->getSd(), message.c_str(), message.length(), 0);
			message = ":server " + std::string(RPL_ENDOFNAMES) + " " + chan->getName() + " :End of NAMES list\r\n";
			send((*it)->getSd(), message.c_str(), message.length(), 0);
		}
		return;
	}
}

void mode::_p_mode_chan(client *cli, channel *chan)
{
	if (_cmd[2][0] == '+')
	{
		chan->setMode('p', true);
		_inform_mode_change("+p", cli, chan);
	}
	else if (_cmd[2][0] == '-')
	{
		chan->setMode('p', false);
		_inform_mode_change("-p", cli, chan);
	}
}

void mode::_s_mode_chan(client *cli, channel *chan)
{
	if (_cmd[2][0] == '+')
	{
		chan->setMode('s', true);
		_inform_mode_change("+s", cli, chan);
	}
	else if (_cmd[2][0] == '-')
	{
		chan->setMode('s', false);
		_inform_mode_change("-s", cli, chan);
	}
}

void mode::_i_mode_chan(client *cli, channel *chan)
{
	if (_cmd[2][0] == '+')
	{
		chan->setMode('i', true);
		_inform_mode_change("+i", cli, chan);
	}
	else if (_cmd[2][0] == '-')
	{
		chan->setMode('i', false);
		_inform_mode_change("-i", cli, chan);
	}
}

void mode::_t_mode_chan(client *cli, channel *chan)
{
	if (_cmd[2][0] == '+')
	{
		chan->setMode('t', true);
		_inform_mode_change("+t", cli, chan);
	}
	else if (_cmd[2][0] == '-')
	{
		chan->setMode('t', false);
		_inform_mode_change("-t", cli, chan);
	}
}

void mode::_n_mode_chan(client *cli, channel *chan)
{
	if (_cmd[2][0] == '+')
	{
		chan->setMode('n', true);
		_inform_mode_change("+n", cli, chan);
	}
	else if (_cmd[2][0] == '-')
	{
		chan->setMode('n', false);
		_inform_mode_change("-n", cli, chan);
	}
}

void mode::_m_mode_chan(client *cli, channel *chan)
{
	if (_cmd[2][0] == '+')
	{
		chan->setMode('m', true);
		_inform_mode_change("+m", cli, chan);
	}
	else if (_cmd[2][0] == '-')
	{
		chan->setMode('m', false);
		_inform_mode_change("-m", cli, chan);
	}
}

void mode::_l_mode_chan(client *cli, channel *chan)
{
	if (_cmd[2][0] == '+')
	{
		chan->setLimitNbr(atoi(_cmd[3].c_str()));
		_inform_mode_change("+l " + _cmd[3], cli, chan);
	}
	else if (_cmd[2][0] == '-')
	{
		chan->setLimitNbr(0);
		_inform_mode_change("-l", cli, chan);
	}
}

void mode::_b_mode_chan(client *cli, channel *chan)
{
	std::string message;
	client *target_cli = chan->getCli(_cmd[3]);

	if (_cmd[3].empty())
	{
		message = ":server " + std::string(ERR_NEEDMOREPARAMS) + " :Mode :Not enough parameters\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
	else if (!chan->isMember(_cmd[3]) && !chan->isBanned(_cmd[3]))
	{
		message = ":server " + std::string(ERR_NOSUCHNICK) + " " + _cmd[3] + " :No such nick\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
	else
	{
		if (_cmd[2][0] == '+' && !chan->isOp(chan->getCli(_cmd[3])))
		{
			chan->addBan(chan->getCli(_cmd[3]));
			_inform_mode_change( "+b on " + target_cli->getNick(), cli, chan);
		}
		else if (_cmd[2][0] == '-')
		{
			chan->deleteBan(_cmd[3]);
			_inform_mode_change( "-b on " + _cmd[3], cli, chan);
		}
		return;
	}
}

void mode::_v_mode_chan(client *cli, channel *chan)
{
	std::string message;
	client *target_cli = chan->getCli(_cmd[3]);

	if (_cmd[3].empty())
	{
		message = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cli->getNick() + " :Mode :Not enough parameters\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
	else if (!chan->isMember(_cmd[3]))
	{
		message = ":server " + std::string(ERR_NOSUCHNICK) + " " + _cmd[3] + " :No such nick\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
	else
	{
		if (_cmd[2][0] == '+' && !chan->isOp(chan->getCli(_cmd[3])))
		{
			chan->addCanSpeak(chan->getCli(_cmd[3]));
			_inform_mode_change( "+v on " + target_cli->getNick(), cli, chan);
		}
		else if (_cmd[2][0] == '-' && chan->isOp(chan->getCli(_cmd[3])))
		{
			chan->deleteCanSpeak(chan->getCli(_cmd[3]));
			_inform_mode_change( "-v on " + target_cli->getNick(), cli, chan);
		}
		return;
	}
}

void mode::_k_mode_chan(client *cli, channel *chan)
{
		std::string message;

	if (_cmd[3].empty())
	{
		message = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cli->getNick() + " :Mode :Not enough parameters\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
	else
	{
		if (_cmd[2][0] == '+')
		{
			chan->setPassword(_cmd[3]);
			_inform_mode_change( "+k", cli, chan);
		}
		else if (_cmd[2][0] == '-')
		{
			chan->setPassword("");
			_inform_mode_change( "-k", cli, chan);
		}
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
		return;
	}
}
