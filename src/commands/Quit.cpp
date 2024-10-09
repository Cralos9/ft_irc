/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:49:40 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/09 13:51:54 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Quit::Quit(Server &server) : ACommand(server)
{
	std::cout << "Quit constructor" << std::endl;
}

Quit::~Quit()
{
	std::cout << "Quit destructor" << std::endl;
}

void Quit::run()
{
	
}