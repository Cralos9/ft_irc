/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:37:43 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/14 17:35:41 by rumachad         ###   ########.fr       */
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
	User &receiver = this->_server.get_user(this->_args.front());
	this->_user->prepare_buffer(this->_user->get_buffer());
	std::cout << this->_user->get_buffer() << std::endl;
	this->_server.msg_user(receiver);
	return (0);
}