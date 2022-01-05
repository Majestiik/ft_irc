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
	size_t i = 0;

	std::cout << BOLDRED << "0" << RESET << std::endl;
	_getCmd(buf);

	if (_cmd.size() > 1 && _cmd[1][0] == '#') /* is mode for chan */
	{
		channel *cur_chan = _getChan(_cmd[1], chan);
		if (cur_chan == NULL)
		{
			std::cout << BOLDRED << "2" << RESET << std::endl;
			message = ":server " + std::string(ERR_NOSUCHCHANNEL) + " " + cli->getNick() + " " + _cmd[1] + " :No such channel\r\n";
			send(cli->getSd(), message.c_str(), message.length(), 0);
			return;
		}
		if (_cmd.size() == 2)
		{
			std::cout << BOLDRED << "1 " + cur_chan->getAllCurrentModes() << RESET << std::endl;
			message = ":server " + std::string(RPL_CHANNELMODEIS) + " " + cli->getNick() + " " + cur_chan->getName() + " :" + cur_chan->getAllCurrentModes() + "\r\n";
			send(cli->getSd(), message.c_str(), message.length(), 0);
			return;
		}
		if (!cur_chan->isOp(cli))
		{
			std::cout << BOLDRED << "3" << RESET << std::endl;
			message = ":server " + std::string(ERR_CHANOPRIVSNEEDED) + " " + cli->getNick() + " " + cur_chan->getName() + " :You're not channel operator\r\n";
			send(cli->getSd(), message.c_str(), message.length(), 0);
			return;
		}
		if (_cmd.size() > 2 && mode.find(_cmd[2][1]) == std::string::npos)
		{
			std::cout << BOLDRED << "4" << RESET << std::endl;
			message = ":server " + std::string(ERR_UNKNOWNMODE) + " " + _cmd[2][1] + " :is unknown mode char\r\n";
			send(cli->getSd(), message.c_str(), message.length(), 0);
			return;
		}
		if (_cmd.size() > 2)
		{
			std::cout << BOLDRED << "5" << RESET << std::endl;
			while (_cmd[2].size() > i)
			{
				if (_cmd[2][i + 1] == 'o')
					_o_mode_chan(cli, cur_chan);
				else if (_cmd[2][i + 1] == 'p')
					_p_mode_chan(cur_chan);
				else if (_cmd[2][i + 1] == 's')
					_s_mode_chan(cur_chan);
				else if (_cmd[2][i + 1] == 'i')
					_i_mode_chan(cur_chan);
				else if (_cmd[2][i + 1] == 't')
					_t_mode_chan(cur_chan);
				else if (_cmd[2][i + 1] == 'n')
					_n_mode_chan(cur_chan);
				else if (_cmd[2][i + 1] == 'm')
					_m_mode_chan(cur_chan);
				else if (_cmd[2][i + 1] == 'l')
					_l_mode_chan(cur_chan);
				else if(_cmd[2][i + 1] == 'b')
					_b_mode_chan(cli, cur_chan);
				else if(_cmd[2][i + 1] == 'v')
					_v_mode_chan(cli, cur_chan);
				else if(_cmd[2][i + 1] == 'k')
					_k_mode_chan(cli, cur_chan);
				i++;
			}
			message = ":server " + std::string(RPL_CHANNELMODEIS) + " " + cli->getNick() + " " + cur_chan->getName() + " :" + cur_chan->getAllCurrentModes() + "\r\n";
			send(cli->getSd(), message.c_str(), message.length(), 0);
		}
	}
	else if (_cmd.size() > 1)/* is mode for cli */
	{
		std::cout << BOLDRED << "6" << RESET << std::endl;
	}
	else
	{
		message = ":server " + std::string(ERR_NEEDMOREPARAMS) + " Mode :Not enough parameters\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
	std::cout << BOLDRED << "7" << RESET << std::endl;
}

void mode::_o_mode_chan(client *cli, channel *chan)
{
	std::string message;

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
		if (_cmd[2][0] == '+' && !chan->isOp(chan->getCli(_cmd[3])))
			chan->addOp(chan->getCli(_cmd[3]));
		else if (_cmd[2][0] == '-' && chan->isOp(chan->getCli(_cmd[3])))
			chan->deleteOp(chan->getCli(_cmd[3]));
		return;
	}
}

void mode::_p_mode_chan(channel *chan)
{
	if (_cmd[2][0] == '+')
		chan->setMode('p', true);
	else if (_cmd[2][0] == '-')
		chan->setMode('p', false);
}

void mode::_s_mode_chan(channel *chan)
{
	if (_cmd[2][0] == '+')
		chan->setMode('s', true);
	else if (_cmd[2][0] == '-')
		chan->setMode('s', false);
}

void mode::_i_mode_chan(channel *chan)
{
	if (_cmd[2][0] == '+')
		chan->setMode('i', true);
	else if (_cmd[2][0] == '-')
		chan->setMode('i', false);
}

void mode::_t_mode_chan(channel *chan)
{
	if (_cmd[2][0] == '+')
		chan->setMode('t', true);
	else if (_cmd[2][0] == '-')
		chan->setMode('t', false);
}

void mode::_n_mode_chan(channel *chan)
{
	if (_cmd[2][0] == '+')
		chan->setMode('n', true);
	else if (_cmd[2][0] == '-')
		chan->setMode('n', false);
}

void mode::_m_mode_chan(channel *chan)
{
	if (_cmd[2][0] == '+')
		chan->setMode('m', true);
	else if (_cmd[2][0] == '-')
		chan->setMode('m', false);
}

void mode::_l_mode_chan(channel *chan)
{
	if (_cmd[2][0] == '+')
	{
		chan->limit_nbr = atoi(_cmd[3].c_str());
	}
	else if (_cmd[2][0] == '-')
		chan->limit_nbr = 0;
}

void mode::_b_mode_chan(client *cli, channel *chan)
{
	std::string message;

	if (_cmd[3].empty())
	{
		message = ":server " + std::string(ERR_NEEDMOREPARAMS) + " :Mode :Not enough parameters\r\n";
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
			chan->addBan(chan->getCli(_cmd[3]));
		else if (_cmd[2][0] == '-' && chan->isOp(chan->getCli(_cmd[3])))
			chan->deleteBan(chan->getCli(_cmd[3]));
		return;
	}
}

void mode::_v_mode_chan(client *cli, channel *chan)
{
	std::string message;

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
			chan->addCanSpeak(chan->getCli(_cmd[3]));
		else if (_cmd[2][0] == '-' && chan->isOp(chan->getCli(_cmd[3])))
			chan->deleteCanSpeak(chan->getCli(_cmd[3]));
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
			chan->setPassword(_cmd[3]);
		else if (_cmd[2][0] == '-')
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