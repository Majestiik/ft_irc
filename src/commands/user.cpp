#include "../../includes/commands/user.hpp"

user::user()
{
}

user::~user()
{
}

int		user::_nbArgs(std::string buf)
{
	int i = 0;
	while (buf.find(' ') != buf.npos)
	{
		i++;
		buf = buf.substr(buf.find(' ') + 1, buf.length() - buf.find(' ') + 1);
	}
	return i;
}

void	user::execute(std::string buf, client *cli)
{
	std::string message;

	buf = buf.substr(5, buf.length() - 5);

	std::string user = buf.substr(0, buf.find(' '));

	std::string realName;

	if (buf.find('*') != buf.npos)
	{
		realName = buf.substr(buf.find('*') + 2, buf.length() - buf.find('*') + 2);
		if (realName[0] == ':')
			realName = realName.substr(1, realName.length() - 1);
		if (realName.find('\r') != buf.npos)
			realName = realName.substr(0, realName.length() - 2);
		else
			realName.pop_back();
	}

	if (realName.empty() || _nbArgs(buf) < 3)
	{
		message = ":server " + std::string(ERR_NEEDMOREPARAMS) + " user :Not enough parameters\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return ;
	}
	if (cli->getLogin().empty() && cli->getRealName().empty())
	{
		cli->setLogin(user);
		cli->setRealName(realName);
	}
	else
	{
		message = ":server " + std::string(ERR_ALREADYREGISTRED) + " user :You may not reregister\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return ;
	}
	if (!cli->getNick().empty())
	{
		message = ":" + cli->getIp() + " 001 " + cli->getNick() + " :Welcome to the IRMEGASTONKS network, you'll see it's incredible\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
	}
}