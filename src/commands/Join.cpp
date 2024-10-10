/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:19:28 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/09 14:28:35 by rumachad         ###   ########.fr       */
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
	std::string channel = _user->second.get_buffer().substr(4, _user->second.get_buffer().find_first_of("\n") - 4 - 1);
	std::cout << "Joining " << channel << " ..." << std::endl;
	std::ostringstream oss;
	oss << "JOIN " << channel << "\r\n";
	_user->second.prepare_buffer(oss.str());
	send(_user->first, _user->second.get_buffer().c_str(), _user->second.get_buffer().length(), 0);
	Channel ch;
	ch.set_name(channel);
	std::vector<Channel>::iterator it = _server.check_channel(ch);
	it->user_list(_user);
	_server.send_msg(_user, 1);
	return (0);
}
	// const std::string channel = this->_args.front();
	// std::cout << "Joining " << channel << " ..." << std::endl;
	// std::ostringstream oss; 
	// oss << "JOIN" << channel << "\r\n";
	// this->_user->prepare_buffer(oss.str());
	// std::cout << this->_user->get_buffer() << std::endl;