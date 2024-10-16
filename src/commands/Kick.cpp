/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:15:15 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/16 18:33:06 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Kick::Kick(Server &server) : ACommand(server)
{
	std::cout << "Kick constructor" << std::endl;
}

Kick::~Kick()
{
	std::cout << "Kick destructor" << std::endl;
}

int Kick::run()
{	
	Channel *ch = this->_server.check_channel(this->_args[0]);

	if (ch != NULL)
	{
		User *kicked = this->_server.get_user(this->_args[1]);
		this->_server.remove_from_ch(*ch, *kicked);
		_user->prepare_buffer(_user->get_buffer());
		this->_server.send_msg_to_channel(*ch, *this->_user, CHSELF);
		std::cout<<_user->get_buffer();
	}
	return(0);
}