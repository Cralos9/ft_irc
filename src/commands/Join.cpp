/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:19:28 by rumachad          #+#    #+#             */
/*   Updated: 2024/11/08 16:17:11 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Join::Join(Server &server) : ACommand(server, false, 1)
{
/* 	std::cout << "Join Server Constructor" << std::endl; */
}

Join::~Join()
{
/* 	std::cout << "Join Destructor" << std::endl; */
}

int Join::run()
{
	const std::string channel = _args[0];

	if (channel[0] != '#')
	{
		_server.send_numeric(*_user, ERR_NOSUCHCHANNEL, "%s :No such channel",
								_args[0].c_str());
		return(1);
	}
	_user->make_msg("JOIN", _args);
	_server.send_msg_one_user(_user->get_fd(), *_user);
	Channel *ch = _server.check_channel(_args[0]);
	if (ch == NULL)
		ch = _server.create_channel(channel);
	ch->add_user(*_user);
	_server.send_msg_to_channel(*ch, *_user, CHSELF);
	return (0);
}
