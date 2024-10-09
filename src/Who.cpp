/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:19:35 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/09 13:20:39 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Who::Who(Server &server) : ACommand(server)
{
	std::cout << "Who constructor" << std::endl;
}

Who::~Who()
{
	std::cout << "Who destructor" << std::endl;
}

void Who::run()
{
	std::cout << "Mode Command" << std::endl;
}