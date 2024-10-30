/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WhoIs.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:18:15 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/30 15:00:30 by rumachad         ###   ########.fr       */
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
		_numeric_args.push_back(_args[0]);
		_server.send_numeric(*_user, ERR_NOSUCHNICK, _numeric_args, ":No such nick");
		return (1);
	}
	else
	{
		/* RPL_WHOISUSER (311) */
		_numeric_args.push_back(_args[0]);
		_numeric_args.push_back(target->get_username());
		_numeric_args.push_back(target->get_hostname());
		_numeric_args.push_back(target->get_realname());
		_server.send_numeric(*_user, RPL_WHOISUSER, _numeric_args, "");
		_numeric_args.erase(_numeric_args.begin(), _numeric_args.end());
		
		/* RPL_WHOISCHANNELS (319) */
		const std::string &user_joined_ch = _server.channels_user_joined(*target);
		if (!user_joined_ch.empty())
			_server.send_numeric(*_user, RPL_WHOISCHANNELS, _numeric_args, ":" + user_joined_ch);
		
		/* RPL_WHOISSERVER (312) */
		_numeric_args.push_back(_args[0]);
		_numeric_args.push_back("localhost");
		_server.send_numeric(*_user, RPL_WHOISSERVER, _numeric_args, ":Vai Trabalhar");
		_numeric_args.erase(_numeric_args.begin(), _numeric_args.end());
	}
	/* RPL_ENDOFWHOIS (318) */
	_numeric_args.push_back(_args[0]);
	_server.send_numeric(*_user, RPL_ENDOFWHOIS, _numeric_args, ":End of /WHOIS list");
	return (0);
}
