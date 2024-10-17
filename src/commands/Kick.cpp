/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:15:15 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/17 11:40:59 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Kick::Kick(Server &server) : ACommand(server)
{
/* 	std::cout << "Kick constructor" << std::endl; */
}

Kick::~Kick()
{
/* 	std::cout << "Kick destructor" << std::endl; */
}

int Kick::run()
{	
	Channel *ch = this->_server.check_channel(this->_args[0]);

	if (ch != NULL)
	{
		User *kicked = this->_server.get_user(this->_args[1]);
		this->_server.remove_from_ch(*ch, *kicked);
		_user->prepare_buffer(_user->get_buffer());
		this->_server.send_msg_all_users(*this->_user, 1);
		std::cout<<_user->get_buffer();
	}
	return(0);
}