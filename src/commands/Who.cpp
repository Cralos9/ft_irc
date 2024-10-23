/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:19:35 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/23 14:39:46 by jmarinho         ###   ########.fr       */
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
   name and nickname if the channel <mask> cannot be found. */
   
Who::Who(Server &server) : ACommand(server)
{
/* 	std::cout << "Who constructor" << std::endl; */
}

Who::~Who()
{
/* 	std::cout << "Who destructor" << std::endl; */
}

int Who::run()
{
	if (_args[0].empty()) //If mask empty list everyone in server
	{
		for (std::map<int, User>::iterator *it; it != _clients.end(); ++it)
		{
			_server.send_msg_all_users(server._clients, _clients, CHSELF);
		}
	}
	// If the mask is a channel, list everyone in the channel
	// If the mask is a user, list the user information
	return (EXIT_SUCCESS);
}