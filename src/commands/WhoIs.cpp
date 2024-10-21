/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WhoIs.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:18:15 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/21 23:10:19 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

WhoIs::WhoIs(Server &server) : ACommand(server)
{
/* 	std::cout << "WhoIs constructor" << std::endl; */
}

WhoIs::~WhoIs()
{
/* 	std::cout << "WhoIs destructor" << std::endl; */
}

const std::string client_rpl(const std::string &hostname, const std::string &nickname
								, const std::string &rpl_numeric)
{
	return (":" + hostname + " " + rpl_numeric + " " + nickname + " ");
}

int WhoIs::run()
{
	User *target = NULL;
	std::string rpl;
	size_t pos = 0;

	target = _server.get_user(_args[0]);
	if (target == NULL)
	{
		std::cout << "User not found" << std::endl;
		return (1);
	}
	/* Prepare rpl */
	rpl = client_rpl(_user->get_hostname(), _user->get_nick(), RPL_WHOISUSER);
	pos = rpl.size();

	/* RPL_WHOISUSER (311) */
	rpl.append(target->get_nick() + " " + target->get_username() + " " +
				target->get_hostname() + " * :" + target->get_realname() + "\r\n");
	_server.print(rpl);
	_user->set_buffer(rpl);
	_server.send_msg_one_user(_user->get_fd(), *_user);
	
	/* RPL_WHOISCHANNELS (319) */
	rpl.erase(pos, rpl.length());
	std::cout << rpl << std::endl;
	rpl.append(target->get_nick() + " :" +); /* Finish. Server function channels_user_joined() can use */
	_server.send_msg_one_user(_user->get_fd(), *_user);
	
	/* RPL_ENDOFWHOIS (318) */
	rpl =
	rpl = ":" + _user->get_hostname() + " " + RPL_ENDOFWHOIS + " " + _user->get_nick()
		+ " " + target->get_nick() + " :End of /WHOIS list" + "\r\n";
	_server.print(rpl);
	_user->set_buffer(rpl);
	_server.send_msg_one_user(_user->get_fd(), *_user);
	return (0);
}