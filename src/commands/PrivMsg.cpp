/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:37:43 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/29 16:14:03 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

PrivMsg::PrivMsg(Server &server, bool usable_pre_reg) : ACommand(server, usable_pre_reg)
{
/* 	std::cout << "PrivMsg constructor" << std::endl;*/
}

PrivMsg::~PrivMsg()
{
/* 	std::cout << "PrivMsg destructor" << std::endl;*/
}

int PrivMsg::run()
{
	Channel *ch = NULL;
	User *receiver = NULL;

	if (this->_args[0].find('#') != std::string::npos)
	{
		ch = _server.check_channel(_args[0]);
		if (ch == NULL)
		{
			const std::string err = client_rpl(_server._hostname, _user->get_nick(),
								ERR_NOSUCHCHANNEL) + _args[0] + " :No such channel\r\n";
			_user->set_buffer(err);
			_server.print(err);
			_server.send_msg_one_user(_user->get_fd(), *_user);
			return (1);
		}
		_user->prepare_buffer(_user->get_buffer());
		_server.print(_user->get_buffer());
		_server.send_msg_to_channel(*ch, *_user, CHOTHER); 
	}
	else
	{
		receiver = this->_server.get_user(this->_args[0]);
		if (receiver == NULL)
		{
			const std::string err = client_rpl(_server._hostname, _user->get_nick(),
								ERR_NOSUCHNICK) + _args[0] + " :No such nick\r\n";
			_user->set_buffer(err);
			_server.print(err);
			_server.send_msg_one_user(_user->get_fd(), *_user);
			return (1);
		}
		_user->prepare_buffer(_user->get_buffer());
		_server.send_msg_one_user(receiver->get_fd(), *_user);
	}
	return (0);
}