/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:42:11 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/28 14:56:49 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Nick::Nick(Server &server, bool usable_pre_reg) : ACommand(server, usable_pre_reg)
{
/* 	std::cout << "Nick Server Constructor" << std::endl; */
}

Nick::~Nick()
{
/* 	std::cout << "Nick Destructor" << std::endl; */
}

int Nick::run()
{
	std::cout << "AHH" << std::endl;
	const std::string nick = _user->get_name(_user->get_buffer(), "NICK ", '\n');
	_user->prepare_buffer(_user->get_buffer());
	std::cout << _user->get_buffer() << std::endl;
	_user->set_nick(nick);
	if (_server.check_nickname(*_user))
	{
		std::string teste = client_rpl(_user->get_hostname(), _user->get_nick(), "433");
		teste = teste + " :Nickname already in use\r\n";
	 	_user->set_buffer(teste);
	}
	_server.send_msg_one_user(_user->get_fd(), *_user);
	return (1);
}