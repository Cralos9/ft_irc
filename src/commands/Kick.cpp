/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:15:15 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/10 12:02:44 by cacarval         ###   ########.fr       */
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

void Kick::run()
{
	
	_server.remove_from_ch(this->_args[0], this->_args[1]);
	_user->second.prepare_buffer(_user->second.get_buffer());
	_server.send_msg(_user, 1);
	std::cout<<_user->second.get_buffer();
}