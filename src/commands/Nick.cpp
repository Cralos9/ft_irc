/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:42:11 by cacarval          #+#    #+#             */
/*   Updated: 2024/11/19 13:58:40 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Nick::Nick(Server &server) : ACommand(server, true, 1)
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
	if (nick.find_first_of("#; ") != std::string::npos)
	{
		if (_user->get_auth())
		{
			_server.send_numeric(*_user, ERR_ERRONEUSNICKNAME, "%s :Erroneus nickname", nick.c_str());
		}
		else
			_server.send_numeric(*_user, ERR_ERRONEUSNICKNAME, "%s :Erroneus nickname", nick.c_str());
		return(1);
	}
	else if (_server.check_nickname(nick))
	{
		if (_user->get_auth())
			_server.send_numeric(*_user, ERR_NICKNAMEINUSE, "%s :Nickname already in use", nick.c_str());
		else
			_server.send_numeric(*_user, ERR_NICKNAMEINUSE, "%s :Nickname already in use", nick.c_str());
		return(1);
	}
	_user->make_msg("NICK", _args);
	if (_user->get_auth() == false)
		_server.send_msg_one_user(_user->get_fd(), *_user);
	_user->set_nick(nick);
	return (1);
}
