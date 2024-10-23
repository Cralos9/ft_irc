/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:19:35 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/21 15:11:14 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Who::Who(Server &server) : ACommand(server)
{
/* 	std::cout << "Who constructor" << std::endl; */
}

Who::~Who()
{
/* 	std::cout << "Who destructor" << std::endl; */
}

int Who::run()
{
	User *user = NULL;

	user = _server.get_user(_args[0]);
	if (user == NULL)
	{
		std::cout << "User does't exists" << std::endl;
		return (1);
	}
	
	return (0);
}