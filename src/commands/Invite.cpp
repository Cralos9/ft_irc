/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:29:10 by jmarinho          #+#    #+#             */
/*   Updated: 2024/11/21 17:20:19by rumachad         ###   ########.fr       */
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
	Channel *ch = NULL;
	User *invited = NULL;

	ch = _server.check_channel(_args[1]);
	if (ch == NULL)
	{
		_server.send_numeric(*_user, ERR_NOSUCHCHANNEL, "%s :No such channel",
								_args[1].c_str());
		return EXIT_FAILURE;
	}

	invited = _server.get_user(_args[0]);
	if (invited == NULL)
	{
		_server.send_numeric(*_user, ERR_NOSUCHNICK, "%s :No such nick", _args[0].c_str());
		return EXIT_FAILURE;
	}

	if (!ch->is_user_on_ch(*_user)) //Check if user is on that channel
	{
		_server.send_numeric(*_user, ERR_NOTONCHANNEL, "%s :You're not on that channel",
								ch->get_name().c_str());
		return (1);
	}

	if (ch->is_user_on_ch(*invited)) //Check if invited_user is already on channel
	{
		_server.send_numeric(*_user, ERR_USERONCHANNEL, "%s :User already on channel",
								_args[0].c_str());
		return (1);
	}
	else if (!ch->is_user_OP(*_user)) //Validate if user is OP
	{
		_server.send_numeric(*_user, ERR_CHANOPRIVSNEEDED, "%s :You're not channel operator",
								ch->get_name().c_str());
		return (1);
	}
	else
	{
		_server.send_numeric(*_user, RPL_INVITING, "%s %s", _args[0].c_str(),
								_args[1].c_str());
		_user->make_msg("INVITE", _args);
		_server.send_msg_one_user(invited->get_fd(), *_user);
		_user->add_invitation(ch->get_name());
	}
	return (0);
}