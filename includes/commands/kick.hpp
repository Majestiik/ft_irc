#include "command.hpp"

class kick : public command
{
	private:
		bool	_checkClientStr(std::string cli, channel *chan);
		void	_informMembers(std::string message, channel *chan);
		client*	_getClient(std::string name, channel *chan);
		kick(kick const& other);
		kick	operator=(kick const& other);

	public:
		kick();
		~kick();
		void	execute(std::string buf, client *cli, std::vector<channel *> *channels, bool isBot, std::string botName);
};