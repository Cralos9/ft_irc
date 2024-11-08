/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:42:11 by cacarval          #+#    #+#             */
/*   Updated: 2024/11/08 10:36:02 by cacarval         ###   ########.fr       */
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
	_user->make_msg("NICK ", _args);
	if (nick.find_first_of("#; ") != std::string::npos)
	{
		if (_user->welcome_flag == false)
		{
			_user->set_nick(nick);
			_user->error_flag = 3;
		}
		else
			_server.send_numeric(*_user, ERR_ERRONEUSNICKNAME, "%s :Erroneus nickname", nick.c_str());
		return(1);
	}
	else if (_server.check_nickname(nick))
	{
		if (_user->welcome_flag == false)
		{
			_user->set_nick(nick);
			_user->error_flag = 2;
		}
		else
			_server.send_numeric(*_user, ERR_NICKNAMEINUSE, "%s :Nickname already in use", nick.c_str());
		return(1);
	}
	if (_user->welcome_flag == true)
		_server.send_msg_one_user(_user->get_fd(), *_user);
	_user->set_nick(nick);
	return (1);
}
