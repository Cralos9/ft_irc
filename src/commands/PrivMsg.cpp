/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:37:43 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/30 14:06:01 by rumachad         ###   ########.fr       */
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
			_numeric_args.push_back(_args[0]);
			_server.send_numeric(*_user, ERR_NOSUCHCHANNEL, _numeric_args, ":No such channel");
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
			_numeric_args.push_back(_args[0]);
			_server.send_numeric(*_user, ERR_NOSUCHNICK, _numeric_args, ":No such nick");
			return (1);
		}
		_user->prepare_buffer(_user->get_buffer());
		_server.send_msg_one_user(receiver->get_fd(), *_user);
	}
	return (0);
}