/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:49:40 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/16 15:05:16 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Quit::Quit(Server &server) : ACommand(server)
{
	std::cout << "Quit constructor" << std::endl;
}

Quit::~Quit()
{
	std::cout << "Quit destructor" << std::endl;
}

int Quit::run()
{
	this->_user->prepare_buffer(this->_user->get_buffer());
	this->_server.send_msg_all_users(*this->_user, 0);
	this->_server.disconnect_user(*this->_user);
	return (1);
}