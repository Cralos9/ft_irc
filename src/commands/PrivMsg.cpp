/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:37:43 by rumachad          #+#    #+#             */
/*   Updated: 2024/11/21 17:44:49 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

PrivMsg::PrivMsg(Server &server) : ACommand(server, false, 2)
{
/* 	std::cout << "PrivMsg constructor" << std::endl;*/
}

PrivMsg::~PrivMsg()
{
/* 	std::cout << "PrivMsg destructor" << std::endl;*/
}

int PrivMsg::run()
{
	Channel	*ch = NULL;
	User	*receiver = NULL;

	std::string target;
	std::istringstream iss(_args[0]);
	std::deque<std::string> params(2);

	if (_args[1].find(':') == std::string::npos)
		_args[1] = ":" + _args[1];

	while (std::getline(iss, target, ','))
	{
		params[0] = target;
		params[1] = _args[1];
		if (target.find('#') != std::string::npos)
		{
			ch = _server.check_channel(target);
			if (ch == NULL)
			{
				_server.send_numeric(*_user, ERR_NOSUCHCHANNEL, "%s :No such channel",
									target.c_str());
				return (1);
			}
			else if (!ch->is_user_on_ch(*_user)) //Check if user is on that Channel
			{
				_server.send_numeric(*_user, ERR_CANNOTSENDTOCHAN, "%s :Cannot send to channel",
										ch->get_name().c_str());
				return (1);
			}
			_user->make_msg("PRIVMSG", params);
			_server.send_msg_to_channel(*ch, *_user, CHOTHER);
		}
		else
		{
			receiver = _server.get_user(target);
			if (receiver == NULL)
			{
				_server.send_numeric(*_user, ERR_NOSUCHNICK, "%s :No such nick",
										target.c_str());
				return (1);
			}
			_user->make_msg("PRIVMSG", params);
			_server.send_msg_one_user(receiver->get_fd(), *_user);
		}
	}
	return (0);
}
