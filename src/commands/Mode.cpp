/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:17:17 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/16 12:23:23 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Mode::Mode(Server &server) : ACommand(server)
{
	std::cout << "Mode constructor" << std::endl;
}

Mode::~Mode()
{
	std::cout << "Mode destructor" << std::endl;
}

int Mode::run()
{
	Channel *ch = this->_server.check_channel(this->_args[0]);
	std::string buffer = this->_user->get_buffer();
	size_t pos = buffer.find_first_of("+-");
	if (ch != NULL)
	{
		if(pos != std::string::npos && buffer[pos + 1] == 'o')
		{
			ch->change_user_it(this->_args[2], buffer[pos]);
			this->_user->prepare_buffer(_user->get_buffer());
			this->_server.send_msg_all_users(*this->_user, 1);
			std::cout << _user->get_buffer() << std::endl;
		}
	}
	return (0);
}