/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:17:17 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/09 13:20:35 by rumachad         ###   ########.fr       */
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

void Mode::run()
{
	std::cout << "Mode Command" << std::endl;
}