/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:37:43 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/10 10:55:38 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

PrivMsg::PrivMsg(Server &server) : ACommand(server)
{
	std::cout << "PrivMsg constructor" << std::endl;
}

PrivMsg::~PrivMsg()
{
	std::cout << "PrivMsg destructor" << std::endl;
}

int PrivMsg::run()
{
	std::cout << "PrivMSG: ";
	std::cout << this->_args.front() << std::endl;
	it_user receiver = this->_server.get_user(this->_args.front());
	std::cout << "Receiver: " << receiver->second.get_nick() << std::endl;
	this->_user->second.prepare_buffer(this->_user->second.get_buffer());
	std::cout << this->_user->second.get_buffer() << std::endl;
	this->_server.msg_user(receiver->first, this->_user->second);
	return (0);
}