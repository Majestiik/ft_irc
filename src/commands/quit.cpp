#include "../../includes/commands/quit.hpp"

quit::quit()
{
}

quit::~quit()
{
}

bool	quit::_alreadyInformed(client *dest, std::vector<client *> informed)
{
	for (std::vector<client *>::iterator it = informed.begin(); it != informed.end(); it++)
	{
		client *search = *it;
		if (search->getNick() == dest->getNick())
			return true;
	}
	return false;
}

void	quit::_informChange(std::string message, client *cli, std::vector<channel *> *channels)
{
	std::vector<client *> informed;
	informed.push_back(cli);

	for (std::vector<channel *>::iterator it = channels->begin(); it != channels->end(); it++)
	{
		channel *c = *it;
		if (c->isMember(cli->getNick()))
		{
			std::vector<client *> cls = c->getMembers();
			for (std::vector<client *>::iterator it2 = cls.begin(); it2 != cls.end(); it2++)
			{
				client *dest = *it2;
				if (!_alreadyInformed(dest, informed))
				{
					send(dest->getSd(), message.c_str(), message.length(), 0);
					informed.push_back(dest);
				}
			}
			c->deleteEverywhere(cli);
		}
	}
}



void	quit::execute(std::string buf, client *cli, std::vector<channel *> *chan)
{
	std::cout << "buf dans quit : " << buf << std::endl;
	std::string bye = buf.substr(5, buf.length() - 5);
	if (bye[0] == ':')
		bye = bye.substr(1, bye.length() - 1);
	//buf = "QUIT : " + cli->getNick() + "\r\n";
	std::cout << "bye : " << bye << std::endl;
	buf = ":" + cli->getNick() + "!" + cli->getLogin() + "@" + cli->getIp() + " QUIT :Quit: " + bye + "\r\n";
	_informChange(buf, cli, chan);

}