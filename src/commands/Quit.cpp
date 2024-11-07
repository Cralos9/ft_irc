/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:49:40 by cacarval          #+#    #+#             */
/*   Updated: 2024/11/07 12:40:15 by rumachad         ###   ########.fr       */
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
	this->_user->make_msg("QUIT", _args);
	this->_server.send_msg_all_users(*this->_user);
	this->_server.disconnect_user(*this->_user);
	return (1);
}