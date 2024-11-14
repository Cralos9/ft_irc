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

UserCMD::UserCMD(Server &server) : ACommand(server, true, 4)
{
/* 	std::cout << "User constructor" << std::endl; */
}

UserCMD::~UserCMD()
{
/* 	std::cout << "UserCMD destructor" << std::endl; */
}

int UserCMD::run()
{
	if (_user->get_auth())
	{
		_server.send_numeric(*_user, ERR_ALREADYREGISTERED, "* :You may not reregister");
		return (0);
	}
	_user->set_username(_args[0]);
	_args[3].erase(_args[3].begin());
	_user->set_realname(_args[3]);
	return (0);
}