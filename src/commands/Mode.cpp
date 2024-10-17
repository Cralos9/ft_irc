/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:17:17 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/17 11:40:54 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Mode::Mode(Server &server) : ACommand(server)
{
/* 	std::cout << "Mode constructor" << std::endl; */
}

Mode::~Mode()
{
/* 	std::cout << "Mode destructor" << std::endl; */
}

int Mode::run()
{
	Channel *ch = this->_server.check_channel(this->_args[0]);
	if (ch != NULL)
	{
		if((this->_user->get_buffer().find_first_of("+o")) != std::string::npos)
		{
			ch->change_user_it(this->_args[2]);
			this->_user->prepare_buffer(_user->get_buffer());
			this->_server.send_msg_all_users(*this->_user, 1);
			std::cout << _user->get_buffer() << std::endl;
		}
	}
	return (0);
}