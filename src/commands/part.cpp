#include "../../includes/commands/part.hpp"

part::part()
{
}

part::~part()
{
}

int		part::_getChannel(std::string name, channel *chan)
{
	int i = 0;
	while (i < 30)
	{
		if (chan[i].getName() == name)
			return i;
		i++;
	}
	return -1;
}

void	part::execute(std::string name, client *cli, channel *chan)
{
	std::cout << "buf dans part : " << name << std::endl;
	int i = _getChannel(name, chan);
	if (i != -1)
	{
		chan[i].deleteClient(cli);
		std::string message = ":127.0.0.1|" + cli->getNick() + "!" + cli->getLogin() + "@" + "127.0.0.1" + " PART " + "/r/n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
	}
	
	

}