/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:49:40 by cacarval          #+#    #+#             */
/*   Updated: 2024/11/26 13:54:53 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Quit::Quit(Server &server) : ACommand(server, true, 0)
{
/* 	std::cout << "Quit constructor" << std::endl; */
}

Quit::~Quit()
{
/* 	std::cout << "Quit destructor" << std::endl; */
}

int Quit::run()
{
	if (_args.empty())
		_args.push_back(":Client Quit");
	_user->make_msg("QUIT", _args);
	std::string ch;
	std::istringstream iss(_server.channels_user_joined(*_user));
	while (std::getline(iss, ch, ' '))
	{
		if (!ch.empty())
			_server.send_msg_to_channel(*_server.check_channel(ch), *this->_user, CHOTHER);
	}
	_server.disconnect_user(*this->_user);
	return (1);
}