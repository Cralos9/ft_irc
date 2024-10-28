/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:57:01 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/28 13:28:22 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Pong::Pong(Server &server, bool usable_pre_reg) : ACommand(server, usable_pre_reg)
{
	std::cout << "Pong constructor" << std::endl;
}

Pong::~Pong()
{
	std::cout << "Pong destructor" << std::endl;
}

int Pong::run()
{
	_user->prepare_buffer("PONG " + _server._server_hostname + " " + _args[0] + "\r\n");
	_server.print(_user->get_buffer());
	_server.send_msg_one_user(_user->get_fd(), *_user);
	return (0);
}