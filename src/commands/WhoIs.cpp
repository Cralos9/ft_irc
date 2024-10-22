/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WhoIs.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:18:15 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/22 14:37:50 by rumachad         ###   ########.fr       */
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

	target = _server.get_user(_args[0]);
	if (target == NULL)
	{
		std::cout << "User not found" << std::endl;
		return (1);
	}

	/* RPL_WHOISUSER (311) */
	rpl.append(client_rpl(_user->get_hostname(), _user->get_nick(), RPL_WHOISUSER));
	rpl.append(target->get_nick() + " " + target->get_username() + " " +
				target->get_hostname() + " * :" + target->get_realname() + "\r\n");
	_server.print(rpl);
	
	/* RPL_WHOISCHANNELS (319) */
	const std::string &user_joined_ch = _server.channels_user_joined(*target);

	if (!user_joined_ch.empty())
	{
		rpl.append(client_rpl(_user->get_hostname(), _user->get_nick(), RPL_WHOISCHANNELS));
		rpl.append(target->get_nick() + " :" + user_joined_ch + "\r\n");
		_server.print(rpl);
	}
	
	/* RPL_WHOISSERVER (312) */
	rpl.append(client_rpl(_user->get_hostname(), _user->get_nick(), RPL_WHOISSERVER));
	rpl.append(target->get_nick() + " localhost :Vai Trabalhar\r\n");
	_server.print(rpl);

	/* RPL_ENDOFWHOIS (318) */
	rpl.append(client_rpl(_user->get_hostname(), _user->get_nick(), RPL_ENDOFWHOIS));
	rpl.append(target->get_nick() + " :End of /WHOIS list\r\n");
	_server.print(rpl);
	_user->set_buffer(rpl);
	_server.send_msg_one_user(_user->get_fd(), *_user);
	return (0);
}
