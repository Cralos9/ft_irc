/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:19:35 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/29 14:13:27 by rumachad         ###   ########.fr       */
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
Who::Who(Server &server, bool usable_pre_reg) : ACommand(server, usable_pre_reg)
{
	/*	std::cout << "Who constructor" << std::endl; */
}

Who::~Who()
{
	/*	std::cout << "Who destructor" << std::endl; */
}

int Who::run()
{
	std::string msg;
	
	if (_args.empty()) // If mask empty list everyone in server
	{
		std::map<int, User> &list = _server.get_all_clients();
		for (std::map<int, User>::iterator it = list.begin(); it != list.end(); ++it) {
			{
				msg = ":" + _server._hostname + " " + "352" + _user->get_nick() + " * "
					+ it->second.get_username() + " " + it->second.get_hostname() + " " + _server._hostname + " "
					+ it->second.get_nick() + " H :0 " + it->second.get_username() + "\r\n";
				
				_user->set_buffer(msg);
				_server.send_msg_one_user(_user->get_fd(), *_user);
				msg.clear();
			}
		}
	}
	else if (_server.check_channel(_args[0]) == NULL && _server.get_user(_args[0]) == NULL)
	{
		msg = ":" + _server._hostname + " 315 " + _user->get_nick() + " :End of WHO list\r\n";
		
		_user->set_buffer(msg);
		_server.send_msg_one_user(_user->get_fd(), *_user);
		msg.clear();
		_args.clear();
		return (EXIT_FAILURE);
	}
	else if (_server.check_channel(_args[0]) != NULL) // If the mask is a channel, list everyone in the channel
	{
		Channel *channel = _server.check_channel(_args[0]);
		std::map<User *, int> users = channel->get_users();

		for (std::map<User *, int>::iterator it = users.begin(); it != users.end(); it++)
		{
			msg = ":" + _server._hostname + " " + "352" + _user->get_nick() + " "
				+ _args[0] + " "+ it->first->get_username() + it->first->get_hostname() + " " + _server._hostname + " "
				+ it->first->get_nick() + " H :0 " + it->first->get_username() + "\r\n";
			
			_user->set_buffer(msg);
			_server.send_msg_one_user(_user->get_fd(), *_user);
			msg.clear();
		}
	}
	else if (_server.get_user(_args[0]) != NULL) // If the mask is a user, list the user information
	{
		User *target = _server.get_user(_args[0]);
		msg = ":" + _server._hostname + " " + "352" + _user->get_nick() + " * "
			+ target->get_username() + target->get_hostname() + " " + _server._hostname + " "
				+ target->get_nick() + " H :0"+ target->get_username() + "\r\n";
		
		_user->set_buffer(msg);
		_server.send_msg_one_user(_user->get_fd(), *_user);
		msg.clear();
	}
	else
	{
		msg = ":" + _server._hostname + " " + "mask not accepted" + "\r\n";
		
		_user->set_buffer(msg);
		_server.send_msg_one_user(_user->get_fd(), *_user);
		msg.clear();
	}
	// General end of WHO list
	msg = ":" + _server._hostname + " 315 " + _user->get_nick() + " :End of WHO list\r\n";
	
	_user->set_buffer(msg);
	_server.send_msg_one_user(_user->get_fd(), *_user);
	msg.clear();
	_args.clear();
	return (EXIT_SUCCESS);
}
