/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:42:11 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/18 10:49:56 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Nick::Nick(Server &server) : ACommand(server)
{
/* 	std::cout << "Nick Server Constructor" << std::endl; */
}

Nick::~Nick()
{
/* 	std::cout << "Nick Destructor" << std::endl; */
}

int Nick::run()
{
	std::string nick = _user->get_name(_user->get_buffer(), "NICK ", '\n');
	_user->prepare_buffer(_user->get_buffer());
	send(_user->get_fd(), _user->get_buffer().c_str(), _user->get_buffer().length(), 0);
	_user->set_nick(nick);
	return (1);
}