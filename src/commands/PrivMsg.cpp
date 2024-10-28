/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:37:43 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/28 13:28:33 by rumachad         ###   ########.fr       */
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
		ch = this->_server.check_channel(this->_args[0]);
		if (ch == NULL)
			return (1);
		this->_user->prepare_buffer(this->_user->get_buffer());
		this->_server.send_msg_to_channel(*ch, *this->_user, CHOTHER); 
		this->_server.print("Sending " + this->_user->get_buffer());
	}
	else
	{
		receiver = this->_server.get_user(this->_args[0]);
		if (receiver == NULL)
		{
			_server.print("No User Found");
			_user->set_buffer(":" + _user->get_hostname() + " 401 " + _user->get_nick() + " " + _args[0] + " :No such nick\r\n");
			_server.send_msg_one_user(_user->get_fd(), *_user);
			return (0);
		}
		this->_user->prepare_buffer(this->_user->get_buffer());
		this->_server.send_msg_one_user(receiver->get_fd(), *this->_user);
	}
	return (0);
}