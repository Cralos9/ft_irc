/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:49:40 by cacarval          #+#    #+#             */
/*   Updated: 2024/11/07 12:34:58 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Quit::Quit(Server &server, bool usable_pre_reg) : ACommand(server, usable_pre_reg)
{
/* 	std::cout << "Quit constructor" << std::endl; */
}

Quit::~Quit()
{
/* 	std::cout << "Quit destructor" << std::endl; */
}

int Quit::run()
{
	std::string hold_buffer = this->_user->get_buffer();
	std::string reason = hold_buffer.substr(hold_buffer.find(":") + 1, hold_buffer.find("\r") - hold_buffer.find(":") - 1);
	this->_user->prepare_buffer("ERROR :Closing Link: " + _user->get_nick() + " " + "(" + reason + ")" + "\r\n");
	this->_server.send_msg_one_user(_user->get_fd(), *_user);
	this->_user->prepare_buffer(hold_buffer);
	this->_server.send_msg_all_users(*this->_user);
	this->_server.disconnect_user(*this->_user);
	return (1);
}