/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:49:40 by cacarval          #+#    #+#             */
/*   Updated: 2024/11/13 12:42:42 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Quit::Quit(Server &server) : ACommand(server, true, 1)
{
/* 	std::cout << "Quit constructor" << std::endl; */
}

Quit::~Quit()
{
/* 	std::cout << "Quit destructor" << std::endl; */
}

int Quit::run()
{
	// std::string hold_buffer = this->_user->get_buffer();
	// std::string reason = "(" + _args[0] + ")";
	// std::vector<std::string> error_args;
	// error_args[0] = this->_user->get_nick();
	// this->_user->make_msg("ERROR :Closing Link: " );
	// this->_server.send_msg_one_user(_user->get_fd(), *_user);
	this->_user->make_msg("QUIT", _args);
	this->_server.send_msg_all_users(*this->_user);
	this->_server.disconnect_user(*this->_user);
	return (1);
}