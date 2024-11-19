/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:17:17 by rumachad          #+#    #+#             */
/*   Updated: 2024/11/18 14:11:29 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Mode::Mode(Server &server) : ACommand(server, false, 1)
{
/* 	std::cout << "Mode constructor" << std::endl; */
}

Mode::~Mode()
{
/* 	std::cout << "Mode destructor" << std::endl; */
}



void Mode::use_modes(char signal, char mode, std::string param, Channel *ch)
{
	User *target = NULL;
	if (mode == 'o')
	{
		target = ch->get_user(param);
		if (target == NULL)
		{
			_server.send_numeric(*_user, ERR_NOSUCHNICK, "%s :No such nick",
									param.c_str());
			return ;
		}
		ch->change_userPrivs(*target, signal);
	}
	else if (mode == 'l')
	{
		int limit = std::atoi(param.c_str());
		if (signal == '-')
		{
			ch->set_user_limit(50);
			ch->set_statusUserLimit(false);
		}
		else if (limit != 0)
		{
			ch->set_user_limit(limit);
			ch->set_statusUserLimit(true);
		}
		else
			return ;
	}
	else if(mode == 'k')
	{
		if (signal == '-')
		{
			ch->set_ch_password("");
			ch->set_statusChannelKey(false);
		}
		else if (signal == '+')
		{
			ch->set_ch_password(param);
			ch->set_statusChannelKey(true);
		}
	}
	else if (mode == 'i')
	{
		if (signal == '-')
			ch->set_statusInviteOnly(false);
		else if (signal == '+')
			ch->set_statusInviteOnly(true);
	}
	else if (mode == 't')
	{
		if (signal == '-')
			ch->set_statusTopicRestrictions(false);
		else if (signal == '+')
			ch->set_statusTopicRestrictions(true);
	}
}

int Mode::run()
{
	Channel *ch = NULL;

	ch = _server.check_channel(_args[0]);
	if (ch == NULL)
	{
		_server.send_numeric(*_user, ERR_NOSUCHCHANNEL, "%s :No such channel",
								_args[0].c_str());
		return (1);
	}
	if (_args.size() == 1)
	{
		std::string msg;

		if (ch->get_activeModes(msg))
			_server.send_numeric(*_user, RPL_CHANNELMODEIS, "%s %s", ch->get_name().c_str(),
									("+" + msg).c_str());
		return (0);
	}

	/* User who executed the command */
	if (ch->is_user_OP(*_user) == false)
	{
		_server.send_numeric(*_user, ERR_CHANOPRIVSNEEDED, "%s :You're not the channel operator",
								_args[0].c_str());
		return (1);
	}

	for(std::deque<std::string>::iterator it = _args.begin(); it != _args.end(); it++)
		std::cout << *it << std::endl;
	size_t pos = _args[1].find_first_of("+-");

	if (pos != std::string::npos)
	{
		size_t j = 1;
		for(size_t i = 1; _args[1][i]; i++)
		{
			if(_args[1][i] == '+' || _args[1][i] == '-')
			{
				pos = i;
				continue;
			}
			if (_args.size() - 1 <= j)
			{
				_args.resize(_args.size() + 1);
				_args[j + 1] = "";
			}
			use_modes(_args[1][pos], _args[1][i], _args[j + 1], ch);
			if (_args[1][i] == 'i')
			{
				std::deque<std::string> invite;
				invite.push_back(ch->get_name());
				invite.push_back(std::string(1, _args[1][pos]) + "i");
				_user->make_msg("MODE", invite);
				_server.send_msg_to_channel(*ch, *_user, CHSELF);
				_args[1].erase(i--, 1);
				continue;
			}
			j++;
		}
	}
	_user->make_msg("MODE", _args);
	_server.send_msg_to_channel(*ch, *_user, CHSELF);
	return (0);
}
