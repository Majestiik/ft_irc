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
		
		if (cur_chan == NULL)
		{
			message = ":server " + std::string(ERR_NOSUCHCHANNEL) + " " + cli->getNick() + " :" + _cmd[1] + " :No such channel\r\n";
			send(cli->getSd(), message.c_str(), message.length(), 0);
			return;
		}
		else if (!cur_chan->isOp(cli))
		{
			message = ":server " + std::string(ERR_CHANOPRIVSNEEDED) + " " + cli->getNick() + " :" + _cmd[1] + " :You're not channel operator\r\n";
			send(cli->getSd(), message.c_str(), message.length(), 0);
			return;
		}
		else
		{

		}
	}

	else /* is mode for cli */
	{

	}
}

void mode::_getCmd(std::string buf)
{
	char delimiter = ' ';
	std::vector<std::string> cmd_tmp;
	std::string line;
	std::stringstream ss(buf);

	while (std::getline(ss, line, delimiter))
		cmd_tmp.push_back(line);

	_cmd.clear();
	_cmd = cmd_tmp;
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
		chan->addOp(chan->getCli(_cmd[2]));
		message = ":server " + std::string(RPL_UMODEIS) + " " + _cmd[2] + " o mod set\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return;
	}
}

void mode::_p_mode_chan()
{

}

void mode::_s_mode_chan()
{

}

void mode::_i_mode_chan()
{

}

void mode::_t_mode_chan()
{

}

void mode::_n_mode_chan()
{

}

void mode::_m_mode_chan()
{

}

void mode::_l_mode_chan()
{

}

void mode::_b_mode_chan()
{

}

void mode::_v_mode_chan()
{

}

void mode::_k_mode_chan()
{

}

void mode::_i_mode_cli()
{

}

void mode::_s_mode_cli()
{

}

void mode::_w_mode_cli()
{

}

void mode::_o_mode_cli()
{

}