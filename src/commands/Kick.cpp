/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:15:15 by cacarval          #+#    #+#             */
/*   Updated: 2024/11/08 16:17:42by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Kick::Kick(Server &server) : ACommand(server, false, 2)
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
	User *target = NULL;

	/* Check if channel exists */
	channel = _server.check_channel(this->_args[0]);
	if (channel == NULL)
	{
		_server.send_numeric(*_user, ERR_NOSUCHCHANNEL, "%s :No such channel",
								_args[0].c_str());
		return (1);
	}

	/* Check if User is in that Channel */
	if (!channel->is_user_on_ch(*_user))
	{
		_server.send_numeric(*_user, ERR_NOTONCHANNEL, "%s :You're not on that channel",
								channel->get_name().c_str());
		return (0);
	}

	/* Check if User has Privlieges */
	if (!channel->is_user_OP(*_user))
	{
		_server.send_numeric(*_user, ERR_CHANOPRIVSNEEDED, "%s :You're not channel operator",
								channel->get_name().c_str());
		return (0);
	}

	/* Check if User exist in the Server */
	if (_server.get_user(_args[1]) == NULL)
	{
		_server.send_numeric(*_user, ERR_NOSUCHNICK, "%s :No such nick",
								_args[1].c_str());
		return (1);
	}

	/* Check if target User exists in the channel */
	target = channel->get_user(this->_args[1]);
	if (target == NULL)
	{
		_server.send_numeric(*_user, ERR_USERNOTINCHANNEL, "%s %s :They aren't on that channel",
								_args[1].c_str(), channel->get_name().c_str());
		return (1);
	}

	_user->make_msg("KICK", _args);
	_server.send_msg_to_channel(*channel, *_user, CHSELF);
	channel->delete_user(*target);
	return(0);
}
