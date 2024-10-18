/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:29:10 by jmarinho          #+#    #+#             */
/*   Updated: 2024/10/18 15:45:47 by jmarinho         ###   ########.fr       */
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

Invite::Invite(Server &server) : ACommand(server)
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

	std::cout << "args0 " << _args[0] << std::endl;
	std::cout << "args1 " << _args[1] << std::endl;
		
	std::string NO_CH_OR_USER = _user->get_hostname() + "401" + _args[0] + ":No such nick/Channel";
	std::string CH_NOT_EXIST = _user->get_hostname() + "403" + _args[1] + ":No such channel";
	
	if (_server.get_user(_args[0]) == NULL)
	{
		std::cout << "USER NAO EXISTE" << std::endl;
		send(_user->get_fd(), NO_CH_OR_USER.c_str(), NO_CH_OR_USER.length(), 0);
		return EXIT_FAILURE;
	}
	else if (_server.check_channel(_args[1]) == NULL)
	{
		std::cout << "CHANNEL NAO EXISTE" << std::endl;
		send(_user->get_fd(), CH_NOT_EXIST.c_str(), CH_NOT_EXIST.length(), 0);
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}