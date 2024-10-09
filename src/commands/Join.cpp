/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:19:28 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/09 13:38:43 by cacarval         ###   ########.fr       */
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

void Join::run()
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
}
	// const std::string channel = this->_args.front();
	// std::cout << "Joining " << channel << " ..." << std::endl;
	// std::ostringstream oss; 
	// oss << "JOIN" << channel << "\r\n";
	// this->_user->prepare_buffer(oss.str());
	// std::cout << this->_user->get_buffer() << std::endl;