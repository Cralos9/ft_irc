/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:42:11 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/29 15:44:40 by rumachad         ###   ########.fr       */
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
	if (_user->welcome_flag == false)
	{
		_user->set_nick(_args[0]);
		return (1);
	}
/* 	if (_server.check_nickname(_args[0]))
	{
		const std::string err = client_rpl(_server._hostname, _user->get_nick(),
								ERR_NICKNAMEINUSE) + _args[0] + " :Nickname already in use\r\n";
		_server.print(err);
	 	_user->set_buffer(err);
		_server.send_msg_one_user(_user->get_fd(), *_user);
		return (1);
	} */
	_user->prepare_buffer("NICK " + _args[0] + "\r\n");
	_server.print(_user->get_buffer());
	_server.send_msg_one_user(_user->get_fd(), *_user);
	_user->set_nick(_args[0]);
	return (1);
}
