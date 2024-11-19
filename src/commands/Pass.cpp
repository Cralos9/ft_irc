/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:33:09 by rumachad          #+#    #+#             */
/*   Updated: 2024/11/20 15:57:50 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Pass::Pass(Server &server) : ACommand(server, true, 1)
{
/* 	std::cout << "Pass constructor" << std::endl; */
}

Pass::~Pass()
{
/* 	std::cout << "Pass destructor" << std::endl; */
}

int Pass::run()
{
	if (_user->get_auth() == false)
		return (0);
	if (_args[0] != _server.get_password())
	{
		std::cout << RED << "Password Error" << RESET << std::endl;
		return (1);
	}
	else
	{
		_user->set_password(_args[0]);
		std::cout << GREEN << "Password Accepted" << RESET << std::endl;
	}
	return (0);
}