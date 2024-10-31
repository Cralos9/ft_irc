/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:29:10 by jmarinho          #+#    #+#             */
/*   Updated: 2024/10/30 16:13:04 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

//https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.7

/* Command: INVITE
   Parameters: <nickname> <channel>

   The INVITE command is used to invite a user to a channel.  The
   parameter <nickname> is the nickname of the person to be invited to
   the target channel <channel>.  There is no requirement that the
   channel the target user is being invited to must exist or be a valid
   channel.  However, if the channel exists, only members of the channel
   are allowed to invite other users.  When the channel has invite-only
   flag set, only channel operators may issue INVITE command. */

Invite::Invite(Server &server, bool usable_pre_reg) : ACommand(server, usable_pre_reg)
{
/* 	std::cout << "Invite Server Constructor" << std::endl; */
}

Invite::~Invite()
{
/* 	std::cout << "Invite Destructor" << std::endl; */
}

int Invite::run()
{
	/* if no Channel or no Nick in buffer
		return to client c1r3s6.42porto.com 401 jmarinho manel :No such nick/Channel
	if channel doesnt exits in channel list
		return to client c1r3s6.42porto.com 403 jmarinho geral :No such channel */
		
	if (_server.get_user(_args[0]) == NULL) // Check if user exists
	{
		_numeric_args.push_back(_args[0]);
		_server.send_numeric(*_user, ERR_NOSUCHNICK, _numeric_args, ":No such nick");
		return EXIT_FAILURE;
	}
	else if (_server.check_channel(_args[1]) == NULL) //Check if channel exists
	{
		_numeric_args.push_back(_args[1]);
		_server.send_numeric(*_user, ERR_NOSUCHNICK, _numeric_args, ":No such nick");
		return EXIT_FAILURE;
	}
	else
	{
		Channel *ch = _server.check_channel(_args[1]);
		User *invited = _server.get_user(_args[0]);
		
		if (ch->is_user_on_ch(*invited)) //Check if user is already on channel
		{
			_server.send_numeric(*_user, ERR_USERONCHANNEL, _numeric_args, ":User already on channel");
			return EXIT_FAILURE;
		}
		else if (ch->is_user_OP(*_user)) //Validate if user is OP
		{
			_numeric_args.push_back(_args[0]);
			_server.send_numeric(*_user, RPL_INVITING, _numeric_args, _args[1]);
			_user->prepare_buffer("INVITE " + _args[0] + " " + _args[1] + "\r\n");
			_server.print(_user->get_buffer());
			_server.send_msg_one_user(invited->get_fd(), *_user);
		}
	}
	return EXIT_SUCCESS;
}