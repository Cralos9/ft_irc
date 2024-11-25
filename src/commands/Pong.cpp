/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:57:01 by rumachad          #+#    #+#             */
/*   Updated: 2024/11/25 11:01:29 by cacarval         ###   ########.fr       */
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

int Pong::run()
{
	_args.insert(_args.begin(), _server.get_host());
	_user->make_msg("PONG", _args);
	_server.send_msg_one_user(_user->get_fd(), *_user);
	return (0);
}