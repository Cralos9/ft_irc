/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:57:01 by rumachad          #+#    #+#             */
/*   Updated: 2024/11/04 13:51:34 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Pong::Pong(Server &server, bool usable_pre_reg) : ACommand(server, usable_pre_reg)
{
/* 	std::cout << "Pong constructor" << std::endl; */
}

Pong::~Pong()
{
/* 	std::cout << "Pong destructor" << std::endl; */
}

int Pong::run()
{
	_user->prepare_buffer("PONG " + _server._hostname + " " + _args[0] + "\r\n");
	_server.send_msg_one_user(_user->get_fd(), *_user);
	return (0);
}