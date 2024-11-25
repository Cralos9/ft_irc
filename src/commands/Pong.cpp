/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:57:01 by rumachad          #+#    #+#             */
/*   Updated: 2024/11/25 12:16:46 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Pong::Pong(Server &server) : ACommand(server, true, 1)
{
/* 	std::cout << "Pong constructor" << std::endl; */
}

Pong::~Pong()
{
/* 	std::cout << "Pong destructor" << std::endl; */
}

// const std::string users_from_channel(const std::map<User *, int> &channel_users)
// {
// 	std::string users;
// 	for (std::map<User *, int>::const_iterator it = channel_users.begin(); it != channel_users.end(); it++)
// 	{
// 		if (it->second == OP)
// 			users.append('@' + it->first->get_nick() + ' ');
// 		else
// 		 	users.append(it->first->get_nick() + " ");
// 	}
// 	return (users);
// }

int Pong::run()
{
	for(std::deque<std::string>::iterator it = _args.begin(); it != _args.end(); it++)
		std::cout << *it << std::endl;
	_args.insert(_args.begin(), _server.get_host());
	_user->make_msg("PONG", _args);
	_server.send_msg_one_user(_user->get_fd(), *_user);
	// _server.send_numeric(*_user, RPL_NAMREPLY, "= %s :%s", ch->get_name().c_str(),
	// 					users_from_channel(ch->get_users()).c_str());
	return (0);
}