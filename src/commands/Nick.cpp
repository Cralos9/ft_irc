/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:42:11 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/09 14:16:29 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Nick::Nick(Server &server) : ACommand(server)
{
	std::cout << "Nick Server Constructor" << std::endl;
}

Nick::~Nick()
{
	std::cout << "Nick Destructor" << std::endl;
}

int Nick::run()
{
	std::string nick = _user->second.get_name(_user->second.get_buffer(), 1);
	_user->second.prepare_buffer(_user->second.get_buffer());
	send(_user->first, _user->second.get_buffer().c_str(), _user->second.get_buffer().length(), 0);
	_user->second.set_nick(nick);
	return (1);
}