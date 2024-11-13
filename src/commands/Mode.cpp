/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:17:17 by rumachad          #+#    #+#             */
/*   Updated: 2024/11/13 14:28:45 by rumachad         ###   ########.fr       */
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

int Mode::run()
{
	Channel *ch = NULL;
	User *target = NULL;
	std::string buffer = _user->get_buffer();
	size_t pos = buffer.find_first_of("+-");

	ch = _server.check_channel(_args[0]);
	if (ch == NULL)
	{
		_server.send_numeric(*_user, ERR_NOSUCHCHANNEL, "%s :No such channel",
								_args[0].c_str());
		return (1);
	}
	if (_args.size() == 1)
	{
		_server.send_numeric(*_user, RPL_CHANNELMODEIS, "%s %s", ch->get_name().c_str(),
								"+itkol");
		return (0);
	}
	/* User who executed the command */
	if (ch->is_user_OP(*_user) == false)
	{
		_server.send_numeric(*_user, ERR_CHANOPRIVSNEEDED, "%s :You're not the channel operator",
								_args[0].c_str());
		return (1);
	}

	/* Target User from the command */
	
	if (pos != std::string::npos && buffer[pos + 1] == 'o')
	{
		target = ch->get_user(_args[2]);
		if (target == NULL)
		{
			_server.send_numeric(*_user, ERR_NOSUCHNICK, "%s :No such nick",
									_args[2].c_str());
			return (1);
		}
		ch->change_user_it(*target, buffer[pos]);
	}
	else if (pos != std::string::npos && buffer[pos + 1] == 'l')
	{
		if (buffer[pos] == '-')
			ch->set_user_limit(50);
		else
			ch->set_user_limit(std::atoi(_args[2].c_str()));
	}
	_user->make_msg("MODE", _args);
	_server.send_msg_to_channel(*ch, *_user, CHSELF);
	return (0);
}