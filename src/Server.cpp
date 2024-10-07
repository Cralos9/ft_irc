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
	/*std::cout << "Server Constructor" << std::endl;*/
}

Server::Server(int port) : active_fd(1)
{
	/*std::cout << "Server port Constructor" << std::endl;*/
	std::memset(&this->_address, 0, sizeof(this->_address));
	this->_address.sin_family = AF_INET;
	this->_address.sin_port = htons(port);
}

Server::~Server()
{
	/*std::cout << "Server Destructor" << std::endl;	*/
}

/* -------------------------------------------- */

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


pollfd Server::connect_client()
{
	pollfd		client;
	sockaddr_in	client_info;
	socklen_t	len = sizeof(client_info);

	client.fd = accept(this->fds[0].fd, (struct sockaddr *)&client_info, &len);
	if (client.fd == -1)
		print_error("Accept Error");
	client.events = POLLIN;
	this->data[client.fd] = User("user", inet_ntoa(client_info.sin_addr));
	this->active_fd++;
	std::cout << "New client " << this->active_fd << " connected" << std::endl;
	return (client);
}

void Server::receive_msg(it_user user)
{
	int msg_bytes;

	char buffer[1024] = {0};
	msg_bytes = recv(user->first, buffer, sizeof(buffer), 0);
	if (msg_bytes == -1)
		print_error("recv Error");
	user->second.set_buffer(buffer);
	std::cout << user->second.get_buffer();
}

void Server::send_msg(it_user msg_sender)
{
	for (it_user user = this->data.begin(); user != this->data.end(); user++)
	{
		if (user != msg_sender)
			send(user->first, user->second.get_buffer().c_str(),
				user->second.get_buffer().length(), 0);
	}
}

int Server::main_loop()
{
	int ret;

	while (1)
	{
		std::vector<pollfd> tmp;
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
				tmp.push_back(this->connect_client());
				it = this->fds.begin();
			}
			else
			{
				it_user user = advance_map(this->data, it->fd);
				this->receive_msg(user);
				user->second.get_info();
				if (this->find_commands(user, it))
					break;
				this->send_msg(user);
			}
		}
		this->fds.insert(this->fds.end(), tmp.begin(), tmp.end());
	}
	return (0);
}

bool Server::find_commands(it_user user, it_fd it)
{
	int pos = 0;

	if ((pos = (user->second.get_buffer().find("JOIN ") )!= std::string::npos))
	{
		this->join_Channel(user);
		return(1);
	}
	else if ((pos = (user->second.get_buffer().find("WHO ") )!= std::string::npos))
		return(1);
	else if ((pos = (user->second.get_buffer().find("MODE ") )!= std::string::npos))
		return(1);
	else if ((pos = (user->second.get_buffer().find("QUIT ") )!= std::string::npos))
	{
		close(user->first);
		this->active_fd--;
		this->fds.erase(it);
 		this->fds.resize(this->active_fd); 
		return(1);
	}
	return(0);
}
