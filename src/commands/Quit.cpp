/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:49:40 by cacarval          #+#    #+#             */
/*   Updated: 2024/11/19 15:16:17 by cacarval         ###   ########.fr       */
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
	this->_user->make_msg("QUIT", _args);
	this->_server.send_msg_all_users(*this->_user);
	this->_server.disconnect_user(*this->_user);
	return (1);
}