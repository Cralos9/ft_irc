/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:19:35 by rumachad          #+#    #+#             */
/*   Updated: 2024/11/12 14:45:53by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

// https://datatracker.ietf.org/doc/html/rfc2812#section-3.6.1

/* Command: WHO
   Parameters: [ <mask> [ "o" ] ]

   The WHO command is used by a client to generate a query which returns
   a list of information which 'matches' the <mask> parameter given by
   the client.  In the absence of the <mask> parameter, all visible
   (users who aren't invisible (user mode +i) and who don't have a
   common channel with the requesting client) are listed.  The same
   result can be achieved by using a <mask> of "0" or any wildcard which
   will end up matching every visible user.

   The <mask> passed to WHO is matched against users' host, server, real
   name and nickname if the channel <mask> cannot be found.
 */
Who::Who(Server &server) : ACommand(server, false, 1)
{
	/*	std::cout << "Who constructor" << std::endl; */
}

Who::~Who()
{
	/*	std::cout << "Who destructor" << std::endl; */
}

int Who::run()
{
	Channel *channel = _server.check_channel(_args[0]);
	User *target = _server.get_user(_args[0]);
	std::string user_joined_ch;
	
	if (channel != NULL)
	{
		const std::map<User *, int> &channel_users = channel->get_users();
		for (std::map<User *, int>::const_iterator it = channel_users.begin(); it != channel_users.end(); it++)
		{
			User &us = *it->first;
			/* Channel, Username, host, server, nick, hp, realname */
			_server.send_numeric(*_user, RPL_WHOREPLY, "%s %s %s %s %s :%s", 
						_args[0].c_str(), us.get_username().c_str(),
						us.get_hostname().c_str(), _server.get_host().c_str(),
						us.get_nick().c_str(), us.get_realname().c_str());
		}
	}
	else if (target != NULL)
	{
		user_joined_ch = _server.channels_user_joined(*target);
		if (user_joined_ch.empty())
			user_joined_ch = "*";
		_server.send_numeric(*_user, RPL_WHOREPLY, "%s %s %s %s %s :%s",
						user_joined_ch.c_str(), target->get_username().c_str(),
						target->get_hostname().c_str(), _server.get_host().c_str(),
						target->get_nick().c_str(), target->get_realname().c_str());
	}
	// General end of WHO list
	_server.send_numeric(*_user, RPL_ENDOFWHO, "%s :End of /WHO list.", _args[0].c_str());
	return (EXIT_SUCCESS);
}
