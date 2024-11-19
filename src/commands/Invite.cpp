/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:29:10 by jmarinho          #+#    #+#             */
/*   Updated: 2024/11/19 15:15:29 by cacarval         ###   ########.fr       */
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

Invite::Invite(Server &server) : ACommand(server, false, 2)
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
		_server.send_numeric(*_user, ERR_NOSUCHNICK, "%s :No such nick", _args[0].c_str());
		return EXIT_FAILURE;
	}
	else if (_server.check_channel(_args[1]) == NULL) //Check if channel exists
	{
		_server.send_numeric(*_user, ERR_NOSUCHCHANNEL, "%s :No such channel",
								_args[1].c_str());
		return EXIT_FAILURE;
	}
	else
	{
		Channel *ch = _server.check_channel(_args[1]);
		User *invited = _server.get_user(_args[0]);
		
		if (ch->is_user_on_ch(*invited)) //Check if user is already on channel
		{
			_server.send_numeric(*_user, ERR_USERONCHANNEL, "%s :User already on channel",
									_args[0].c_str());
			return EXIT_FAILURE;
		}
		else if (ch->is_user_OP(*_user)) //Validate if user is OP
		{
			_server.send_numeric(*_user, RPL_INVITING, "%s %s", _args[0].c_str(),
									_args[1].c_str());
			_user->make_msg("INVITE", _args);
			_server.print(_user->get_buffer());
			_server.send_msg_one_user(invited->get_fd(), *_user);
			invited->get_invited_channels().push_back(ch->get_name());
		}
	}
	return EXIT_SUCCESS;
}