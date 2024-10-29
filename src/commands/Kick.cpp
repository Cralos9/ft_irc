/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:15:15 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/29 14:52:12 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Kick::Kick(Server &server, bool usable_pre_reg) : ACommand(server, usable_pre_reg)
{
/* 	std::cout << "Kick constructor" << std::endl; */
}

Kick::~Kick()
{
/* 	std::cout << "Kick destructor" << std::endl; */
}

int Kick::run()
{	
	Channel *channel = NULL;
	User *kicked = NULL;

	/* Check if channel exists */
	channel = _server.check_channel(this->_args[0]);
	if (channel == NULL)
	{
		const std::string err = client_rpl(_server._hostname, _user->get_nick(),
								ERR_NOSUCHCHANNEL) + _args[0] + ":No such channel\r\n";
		_server.print(err);
		_user->set_buffer(err);
		_server.send_msg_one_user(_user->get_fd(), *_user);
		return (1);
	}

	/* Check if target user exists */
	kicked = channel->get_user(this->_args[1]);
	if (kicked == NULL)
	{
		const std::string err = client_rpl(_server._hostname, _user->get_nick(),
								ERR_USERNOTINCHANNEL) + _args[1] + " " + _args[0] +
								" :They aren't on that channel\r\n";
		_server.print(err);
		_user->set_buffer(err);
		_server.send_msg_one_user(_user->get_fd(), *_user);
		return (1);
	}

	channel->delete_user_vec(*kicked);
	_user->prepare_buffer(_user->get_buffer());
	this->_server.send_msg_to_channel(*channel, *this->_user, CHSELF);
	_server.print(_user->get_buffer());
	return(0);
}
