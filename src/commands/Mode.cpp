/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:17:17 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/17 14:24:12 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Mode::Mode(Server &server) : ACommand(server)
{
	std::cout << "Mode constructor" << std::endl;
}

Mode::~Mode()
{
	std::cout << "Mode destructor" << std::endl;
}

int Mode::run()
{
	Channel *ch = NULL;
	User *user = NULL;
	std::string buffer = _user->get_buffer();
	size_t pos = buffer.find_first_of("+-");

	if (_args.size() == 1)
		return (1);
	ch = _server.check_channel(_args[0]);
	if (ch == NULL) {
		_server.print("No Channel Found");
		return (1);
	}
	if (ch->is_user_OP(*_user) == false) {
		_server.print(_user->get_nick() + " is not OP");
		return (1);
	}
	user = ch->get_user(_args[2]);
	if (user == NULL) {
		_server.print("User doesn't have OP");
		return (1);
	}
	if (pos != std::string::npos && buffer[pos + 1] == 'o')
	{
		ch->change_user_it(*user, buffer[pos]);
		_user->prepare_buffer(_user->get_buffer());
		_server.send_msg_to_channel(*ch, *_user, CHSELF);
		_server.print(_user->get_buffer());
	}
	return (0);
}