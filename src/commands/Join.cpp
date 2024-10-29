/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:19:28 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/29 15:03:02 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Join::Join(Server &server, bool usable_pre_reg) : ACommand(server, usable_pre_reg)
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
		const std::string err = client_rpl(_server._hostname, _user->get_nick(),
								ERR_NOSUCHCHANNEL) + channel + " :No such channel\r\n";
		_user->set_buffer(err);
		_server.send_msg_one_user(_user->get_fd(), *_user);
		return(1);
	}
	_user->prepare_buffer("JOIN " + channel + "\r\n");
	_server.send_msg_one_user(_user->get_fd(), *_user);
	Channel *ch = _server.check_channel(_args[0]);
	if (ch == NULL)
		ch = _server.create_channel(channel);
	ch->add_user(*_user);
	_server.print(_user->get_buffer());
	_server.send_msg_to_channel(*ch, *_user, CHSELF);
	return (0);
}
