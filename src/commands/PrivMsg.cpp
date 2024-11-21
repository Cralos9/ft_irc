/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:37:43 by rumachad          #+#    #+#             */
/*   Updated: 2024/11/08 17:04:24 by rumachad         ###   ########.fr       */
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
	std::deque<std::string> params = _args;

	if (_args[1].find(':') != std::string::npos)
		_args[1].erase(0, 1);


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
				return (EXIT_FAILURE);
			}
			_user->make_msg("PRIVMSG", params);
			_server.send_msg_to_channel(*ch, *_user, CHOTHER);
		}
		else
		{
			receiver = this->_server.get_user(target);
			if (receiver == NULL)
			{
				_server.send_numeric(*_user, ERR_NOSUCHNICK, "%s :No such nick",
										target.c_str());
				return (EXIT_FAILURE);
			}
			_user->make_msg("PRIVMSG", params);
			_server.send_msg_one_user(receiver->get_fd(), *_user);
		}
	}
	return (EXIT_SUCCESS);
}
