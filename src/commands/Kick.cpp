/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:15:15 by cacarval          #+#    #+#             */
/*   Updated: 2024/11/07 12:38:19 by rumachad         ###   ########.fr       */
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
		_server.send_numeric(*_user, ERR_NOSUCHCHANNEL, "%s :No such channel",
								_args[0].c_str());
		return (1);
	}

	/* Check if target user exists */
	kicked = channel->get_user(this->_args[1]);
	if (kicked == NULL)
	{
		_server.send_numeric(*_user, ERR_USERNOTINCHANNEL, "%s %s :They aren't on that channel",
								_args[1].c_str(), channel->get_name().c_str());
		return (1);
	}

	_user->make_msg("KICK", _args);
	_server.send_msg_to_channel(*channel, *_user, CHSELF);
	channel->delete_user(*kicked);
	return(0);
}
