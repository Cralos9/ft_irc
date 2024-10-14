/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:19:28 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/14 17:19:04 by rumachad         ###   ########.fr       */
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
	std::string channel = _user->get_buffer().substr(4, _user->get_buffer().find_first_of("\n") - 4 - 1);
	std::cout << "Joining " << channel << " ..." << std::endl;

	std::ostringstream oss;
	oss << "JOIN " << channel << "\r\n";
	_user->prepare_buffer(oss.str());
	this->_server.msg_user(*this->_user);
	Channel *ch = this->_server.check_channel(this->_args[0]);
	if (ch == NULL)
		this->_server.create_channel(*this->_user, this->_args[0]);
	else
		this->_server.add_user_channel(*this->_user, *ch);
	this->_server.send_msg(*this->_user, 1);
	return (0);
}
	// const std::string channel = this->_args.front();
	// std::cout << "Joining " << channel << " ..." << std::endl;
	// std::ostringstream oss; 
	// oss << "JOIN" << channel << "\r\n";
	// this->_user->prepare_buffer(oss.str());
	// std::cout << this->_user->get_buffer() << std::endl;