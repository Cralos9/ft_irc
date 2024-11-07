/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCMD.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:58:46 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/28 16:07:29by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

UserCMD::UserCMD(Server &server, bool usable_pre_reg) : ACommand(server, usable_pre_reg)
{
/* 	std::cout << "User constructor" << std::endl; */
}

UserCMD::~UserCMD()
{
/* 	std::cout << "UserCMD destructor" << std::endl; */
}

int UserCMD::run()
{
/* 	if (_user->get_auth())
	{
		_user->set_buffer(client_rpl(_server._hostname, _user->get_nick(), ERR_ALREADYREGISTERED)
							+ ":You may not register\r\n");
		_server.send_msg_one_user(_user->get_fd(), *_user);
	} */
	_user->set_username(_args[0]);
	_user->set_realname(_args[3]);
	return (0);
}