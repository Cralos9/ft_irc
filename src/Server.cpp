/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:23:16 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/02 16:55:87by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/* Constructors/Destructors */
Server::Server()
{
	std::cout << "Server Constructor" << std::endl;
}

Server::Server(int port) : active_fd(1)
{
	std::cout << "Server port Constructor" << std::endl;
	std::memset(&this->_address, 0, sizeof(this->_address));
	this->_address.sin_family = AF_INET;
	this->_address.sin_port = htons(port);
}

Server::~Server()
{
	std::cout << "Server Destructor" << std::endl;	
}

/* -------------------------------------------- */

void Server::find_commands(std::string buffer, int fd)
{
	int pos = 0;
	if ((pos = (buffer.find("JOIN ") )!= std::string::npos))
		this->join_Channel(buffer, pos + 4, fd);
}

int Server::create_server()
{
	int on = 1;
	pollfd sock;

	sock.fd = socket(this->_address.sin_family, SOCK_STREAM, 0);
	if (sock.fd == -1)
		print_error("Socket Error");
	if (setsockopt(sock.fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)))
		print_error("setsockopt Error");
	if (bind(sock.fd, (struct sockaddr *)&this->_address, 
				sizeof(this->_address)) != 0)
		print_error("Bind Error");
	if (listen(sock.fd, 5) == -1)
		print_error("Listen Error");
	sock.events = POLLIN;
	this->fds.push_back(sock);
	return (EXIT_SUCCESS);
}

std::string get_name(std::string string)
{
	if (string.find("NICK ") != std::string::npos)
	{
		int pos = string.find("NICK ") + 5;
		return(string.substr(pos, (string ).find_first_of("\n", pos) - pos - 1));
	}
	return("ERROR");
}

int Server::connect_client()
{
	pollfd client;
	client.fd = accept(this->fds[0].fd, NULL, NULL);
	if (client.fd == -1)
		print_error("Accept Error");
	client.events = POLLIN;
	std::cout << "New client " << this->active_fd << " connected" << std::endl;
	this->fds.push_back(client);
	this->active_fd++;
	return (0);
}

int Server::main_loop()
{
	int ret;

	while (1)
	{
		ret = poll(this->fds.data(), this->active_fd, -1);
		if (ret == -1)
			print_error("Poll Error");
		if (ret == 0)
		{
			std::cout << "Pool timeout" << std::endl;
			return (EXIT_FAILURE);
		}
		for (it_fd it = this->fds.begin(); it != this->fds.end(); it++)
		{
			if (it->revents == 0)
				continue;
			if (it->revents != POLLIN)
				print_error("Error revents");
			if (it->fd == this->fds[0].fd)
			{
				this->connect_client();
				it = this->fds.begin();
			}
			else
			{
				char buffer[1024] = {0};
				ret = recv(it->fd, buffer, sizeof(buffer), 0);
				if (ret == 0)
				{
					std::cout << "Client " << std::distance(this->fds.begin(), it) << " disconnected" << std::endl;
					close(it->fd);
					this->active_fd--;
					this->fds.erase(it);
/* 					this->fds.resize(this->active_fd); */
					continue;
				}
				if (ret == -1)
					print_error("Recv Error");
				this->find_commands(buffer, it->fd);
				std::string name = get_name(buffer);
				if (name != "ERROR")
				{
					User user(name);
					this->data[user] = *it;
					continue;
				}
				std::string teste = get_message(buffer, std::distance(this->fds.begin(), it));
				std::cout << teste;
				for (it_fd it_send = this->fds.begin() + 1; it_send != this->fds.end(); it_send++)
				{
					if (it != it_send)
						send(it_send->fd, teste.c_str(), teste.length(), 0);
				}
			}
		}
	}
	return (0);
}

int Server::get_fd() const {return (this->fds.at(0).fd);}
