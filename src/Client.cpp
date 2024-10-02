/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:39:48 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/02 14:43:02 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client() : _fd(0)
{
	std::cout << "Client Constructor" << std::endl;
}

Client::Client(const int fd) : _fd(fd)
{
	std::cout << "Client Fd constructor" << std::endl;
}

Client::~Client()
{
	std::cout << "Client Destructor" << std::endl;	
	close(this->_fd);
}

/* ----------------------------------------------- */

