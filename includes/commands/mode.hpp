#pragma once

#include "command.hpp"

class mode : public command
{
	private:
		void _inform_mode_change(std::string mode, client *cli, channel *chan);
		void _o_mode_chan(client *cli, channel *chan);
		void _p_mode_chan(client *cli, channel *chan);
		void _s_mode_chan(client *cli, channel *chan);
		void _i_mode_chan(client *cli, channel *chan);
		void _t_mode_chan(client *cli, channel *chan);
		void _n_mode_chan(client *cli, channel *chan);
		void _m_mode_chan(client *cli, channel *chan);
		void _l_mode_chan(client *cli, channel *chan);
		void _b_mode_chan(client *cli, channel *chan);
		void _v_mode_chan(client *cli, channel *chan);
		void _k_mode_chan(client *cli, channel *chan);
		void _i_mode_cli(client *cli, channel *chan);
		void _s_mode_cli(client *cli, channel *chan);
		void _w_mode_cli(client *cli, channel *chan);
		void _o_mode_cli(client *cli, channel *chan);
		mode(mode const& other);
		mode	operator=(mode const& other);

	public:
		mode();
		~mode();
		void	execute(std::string buf, client *cli, std::vector<channel *> *chan);
};