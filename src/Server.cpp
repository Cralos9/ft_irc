/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:23:16 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/02 12:14:11 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/* Constructors/Destructors */
Server::Server()
{
	std::cout << "Server Constructor" << std::endl;
}

Server::Server(int port)
{
	std::cout << "Server port Constructor" << std::endl;
	this->_fd = 0;
	std::memset(&this->_address, 0, sizeof(this->_address));
	this->_address.sin_family = AF_INET;
	this->_address.sin_port = htons(port);
}

Server::~Server()
{
	std::cout << "Server Destructor" << std::endl;	
	close(this->_fd);
}

/* -------------------------------------------- */

int Server::create_server()
{
	int on = 0;
	this->_fd = socket(this->_address.sin_family, SOCK_STREAM, 0);
	if (this->_fd == -1)
		print_error("Socket Error");
	setsockopt(this->_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	if (bind(this->_fd, (struct sockaddr *)&this->_address, 
				sizeof(this->_address)) != 0)
		print_error("Bind Error");
	if (listen(this->_fd, 5) == -1)
		print_error("Listen Error");
	return (EXIT_SUCCESS);
}

int Server::get_fd() const {return (this->_fd);}
