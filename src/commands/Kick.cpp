/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:15:15 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/30 14:05:00 by rumachad         ###   ########.fr       */
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

	std::vector<std::string> t;
	/* Check if channel exists */
	channel = _server.check_channel(this->_args[0]);
	if (channel == NULL)
	{
		_numeric_args.push_back(_args[0]);
		_server.send_numeric(*_user, ERR_NOSUCHCHANNEL, _numeric_args, ":No such channel");
		return (1);
	}

	/* Check if target user exists */
	kicked = channel->get_user(this->_args[1]);
	if (kicked == NULL)
	{
		_numeric_args.push_back(_args[1]);
		_numeric_args.push_back(_args[0]);
		_server.send_numeric(*_user, ERR_USERNOTINCHANNEL, _numeric_args, ":They aren't on that channel");
		return (1);
	}

	channel->delete_user_vec(*kicked);
	_user->prepare_buffer(_user->get_buffer());
	_server.send_msg_to_channel(*channel, *_user, CHSELF);
	_server.print(_user->get_buffer());
	return(0);
}
