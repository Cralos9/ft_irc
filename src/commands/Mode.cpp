/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:17:17 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/10 15:00:31 by cacarval         ###   ########.fr       */
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
	if((_user->second.get_buffer().find_first_of("+o")) != std::string::npos)
	{
		std::string ch_name = this->_args[0];
		Channel ch;
		ch.set_name(" " + ch_name);
		std::vector<Channel>::iterator it = _server.check_channel(ch);
		it->change_user_it(this->_args[2]);
		_user->second.prepare_buffer(_user->second.get_buffer());
		_server.send_msg(_user, 1);
		std::cout << _user->second.get_buffer() << std::endl;
	}
		return (0);
}