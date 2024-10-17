/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:49:40 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/17 11:40:33 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Quit::Quit(Server &server) : ACommand(server)
{
/* 	std::cout << "Quit constructor" << std::endl; */
}

Quit::~Quit()
{
/* 	std::cout << "Quit destructor" << std::endl; */
}

int Quit::run()
{
	this->_server.disconnect_user(*this->_user);
	return (1);
}