/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WhoIs.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:18:15 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/31 15:53:04 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

WhoIs::WhoIs(Server &server, bool usable_pre_reg) : ACommand(server, usable_pre_reg)
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
	std::string rpl;

	target = _server.get_user(_args[0]);
	if (target == NULL)
	{
		_server.send_numeric(*_user, ERR_NOSUCHNICK, "%s :No such nick", _args[0].c_str());
		return (1);
	}
	else
	{
		/* RPL_WHOISUSER (311) */
		_server.send_numeric(*_user, RPL_WHOISUSER, "%s %s %s * :%s", target->get_nick().c_str(),
								target->get_username().c_str(), target->get_hostname().c_str(),
								target->get_realname().c_str());

		/* RPL_WHOISCHANNELS (319) */
		const std::string &user_joined_ch = _server.channels_user_joined(*target);
		if (!user_joined_ch.empty())
			_server.send_numeric(*_user, RPL_WHOISCHANNELS, "%s :%s", target->get_nick().c_str(),
									user_joined_ch.c_str());

		/* RPL_WHOISSERVER (312) */
		_server.send_numeric(*_user, RPL_WHOISSERVER, "%s %s :Vai Trabalhar",
								target->get_nick().c_str(), SERVER_NAME);
	}
	/* RPL_ENDOFWHOIS (318) */
	_server.send_numeric(*_user, RPL_ENDOFWHOIS, "%s :End of /WHOIS list", target->get_nick().c_str());
	return (0);
}
