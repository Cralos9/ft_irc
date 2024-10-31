/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:42:11 by cacarval          #+#    #+#             */
/*   Updated: 2024/11/04 14:08:28 by rumachad         ###   ########.fr       */
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
	std::string nick = _args[0];
	_user->prepare_buffer("NICK " + _args[0] + "\r\n");
	if (_server.check_nickname(nick))
	{
		_user->set_nick(nick);
		_user->error_flag = 2;
		return(1);
	}
	if (_user->welcome_flag == true)
		_server.send_msg_one_user(_user->get_fd(), *_user);
	_user->set_nick(nick);
	return (1);
}
