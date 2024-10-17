/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:15:15 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/17 13:39:47 by rumachad         ###   ########.fr       */
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
	Channel *ch = NULL;
	User *kicked = NULL;

	ch = _server.check_channel(this->_args[0]);
	if (ch == NULL)
		return (0);
	kicked = ch->get_user(this->_args[1]);
	if (kicked == NULL)
		return (0);
	ch->delete_user_vec(*kicked);
	_user->prepare_buffer(_user->get_buffer());
	this->_server.send_msg_to_channel(*ch, *this->_user, CHSELF);
	_server.print(_user->get_buffer());
	return(0);
}