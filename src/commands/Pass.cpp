/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:33:09 by rumachad          #+#    #+#             */
/*   Updated: 2024/11/07 12:17:15 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Pass::Pass(Server &server, bool usable_pre_reg) : ACommand(server, usable_pre_reg)
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
	_user->set_password(_args[0]);
	if (!(_server.check_password(*_user)))
	{
		std::cout << RED << "Password Error" << RESET << std::endl;
		_user->error_flag = 1;
		return (1);
	}
	else
	{
		std::cout << GREEN << "Password Accepted" << RESET << std::endl;
		_user->set_auth(false);
	}
	return (0);
}