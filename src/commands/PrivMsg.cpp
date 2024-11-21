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

	if (_args[1].find(':') != std::string::npos)
		_args[1].erase(0, 1);

	while (std::getline(iss, target, ','))
	{
		if (target.find('#') != std::string::npos)
		{
			ch = _server.check_channel(target);
			if (ch == NULL)
			{
				_server.send_numeric(*_user, ERR_NOSUCHCHANNEL, "%s :No such channel",
									target.c_str());
				return (EXIT_FAILURE);
			}
			std::cout << "target in channel " << target << " msg " << _args[1] << std::endl;

			_user->set_buffer(":" + _user->get_nick() + "!" + _user->get_username() + "@" + _user->get_hostname() + " " + "PRIVMSG " + target + " :" + _args[1] + "\r\n");
			_server.send_msg_to_channel(*ch, *_user, CHOTHER);
			ch = NULL;
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
			std::cout << "target in user " << target << " msg " << _args[1] << std::endl;

			_user->set_buffer(":" + _user->get_nick() + "!" + _user->get_username() + "@" + _user->get_hostname() + " " + "PRIVMSG " + target + " :" + _args[1] + "\r\n");
			_server.send_msg_one_user(receiver->get_fd(), *_user);
			receiver = NULL;
		}
		_user->erase_buffer();
		target.clear();
	}
	return (EXIT_SUCCESS);
}
