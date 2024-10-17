/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:37:43 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/17 11:40:42 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

PrivMsg::PrivMsg(Server &server) : ACommand(server)
{
/* 	std::cout << "PrivMsg constructor" << std::endl; */
}

PrivMsg::~PrivMsg()
{
/* 	std::cout << "PrivMsg destructor" << std::endl; */
}

int PrivMsg::run()
{
	Channel *ch = NULL;
	User *receiver = NULL;

	if (this->_args[0].find('#') != std::string::npos)
	{
		ch = this->_server.check_channel(this->_args[0]);
		this->_user->prepare_buffer(this->_user->get_buffer());
		/* Preciso fazer funcao de mensage só par o channel */
		this->_server.send_msg_all_users(*this->_user, 0); 
		this->_server.print("Sending " + this->_user->get_buffer() + " to " + ch->get_name());
	}
	else
	{
		receiver = this->_server.get_user(this->_args[0]);
		std::cout << receiver->get_nick() << std::endl;
		this->_user->prepare_buffer(this->_user->get_buffer());
		this->_server.send_msg_one_user(receiver->get_fd(), *this->_user);
	}
	return (0);
}