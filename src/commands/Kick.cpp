/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:15:15 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/15 16:49:58 by rumachad         ###   ########.fr       */
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
		this->_server.send_msg_all_users(*this->_user, 1);
		std::cout<<_user->get_buffer();
	}
	return(0);
}