#include "../../includes/commands/quit.hpp"

quit::quit()
{
}

quit::~quit()
{
}

void	quit::execute(std::string buf, client *cli, channel *chan)
{
	(void)buf;
	int i = 0;
	while(i < 30)
	{
		chan[i].deleteClient(cli);
		i++;
	}
}