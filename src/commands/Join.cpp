/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:19:28 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/17 11:53:04 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Join::Join(Server &server) : ACommand(server)
{
	std::cout << "Join Server Constructor" << std::endl;
}

Join::~Join()
{
	std::cout << "Join Destructor" << std::endl;
}

int Join::run()
{
	const std::string channel = _args[0];
	std::ostringstream oss;
	_server.print("Joining " + channel + "...");

	oss << "JOIN " << channel << "\r\n";
	_user->prepare_buffer(oss.str());
	_server.send_msg_one_user(_user->get_fd(), *_user);
	Channel *ch = _server.check_channel(_args[0]);
	if (ch == NULL)
		ch = _server.create_channel(channel);
	ch->add_user(*_user);
	_server.print(_user->get_buffer());
	_server.send_msg_to_channel(*ch, *_user, CHSELF);
	_server.print("Joined " + channel);
	return (0);
}
