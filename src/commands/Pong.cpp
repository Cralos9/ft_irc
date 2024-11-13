/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:57:01 by rumachad          #+#    #+#             */
/*   Updated: 2024/11/12 16:24:59 by rumachad         ###   ########.fr       */
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
	_args.insert(_args.begin(), _server._hostname);
	_user->make_msg("PONG", _args);
	_server.send_msg_one_user(_user->get_fd(), *_user);
	return (0);
}