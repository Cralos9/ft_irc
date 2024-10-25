/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WhoIs.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:18:15 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/25 15:26:20 by rumachad         ###   ########.fr       */
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



int WhoIs::run()
{
	User *target = NULL;
	const std::string target_nick = _args[0];
	std::string rpl;

	target = _server.get_user(_args[0]);
	if (target == NULL)
		rpl = ERR_NOSUCHNICK(_user->get_nick(), _args[0]);
	else
	{
		/* RPL_WHOISUSER (311) */
		rpl.append(client_rpl(_user->get_hostname(), _user->get_nick(), RPL_WHOISUSER));
		rpl.append(target_nick + " " + target->get_username() + " " +
					target->get_hostname() + " * :" + target->get_realname() + "\r\n");
		_server.print(rpl);
		
		/* RPL_WHOISCHANNELS (319) */
		const std::string &user_joined_ch = _server.channels_user_joined(*target);
		if (!user_joined_ch.empty())
		{
			rpl.append(client_rpl(_user->get_hostname(), _user->get_nick(), RPL_WHOISCHANNELS));
			rpl.append(target_nick + " :" + user_joined_ch + "\r\n");
			_server.print(rpl);
		}
		
		/* RPL_WHOISSERVER (312) */
		rpl.append(client_rpl(_user->get_hostname(), _user->get_nick(), RPL_WHOISSERVER));
		rpl.append(target_nick + " localhost :Vai Trabalhar\r\n");
		_server.print(rpl);
	}
	/* RPL_ENDOFWHOIS (318) */
	rpl.append(client_rpl(_user->get_hostname(), _user->get_nick(), RPL_ENDOFWHOIS));
	rpl.append(target_nick + " :End of /WHOIS list\r\n");
	_server.print(rpl);
	_user->set_buffer(rpl);
	_server.send_msg_one_user(_user->get_fd(), *_user);
	return (0);
}
