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
Server::Server(int port) : active_fd(1)
{
	/*std::cout << "Server port Constructor" << std::endl;*/
	std::memset(&this->_address, 0, sizeof(this->_address));
	this->_address.sin_family = AF_INET;
	this->_address.sin_port = htons(port);
	this->_commands["JOIN"] = new Join(*this);
	this->_commands["WHO"] = new Who(*this);
	this->_commands["MODE"] = new Mode(*this);
	this->_commands["NICK"] = new Nick(*this);
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

void Server::close_all_fds()
{
	for (it_fd it = this->fds.begin(); it != this->fds.end(); it++)
		close(it->fd);
	this->fds.erase(this->fds.begin(), this->fds.end());
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
	this->_clients[client.fd] = User(inet_ntoa(client_info.sin_addr));
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
	std::cout << buffer;
}

void Server::send_msg(it_user msg_sender, int i)
{
	for (it_user user = this->_clients.begin(); user != this->_clients.end(); user++)
	{
		if (user != msg_sender && i == 0)
			send(user->first, msg_sender->second.get_buffer().c_str(),
				msg_sender->second.get_buffer().length(), 0);
		else if (i == 1)
			send(user->first, msg_sender->second.get_buffer().c_str(),
				msg_sender->second.get_buffer().length(), 0);
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
				it_user user = advance_map(this->_clients, it->fd);
				this->receive_msg(user);
				if(user->second.get_info())
					break;
				this->handle_commands(user);
				/* if (this->find_commands(user, it))
					break; */
				user->second.prepare_buffer(user->second.get_buffer());
				this->send_msg(user, 0);
			}
		}
		this->fds.insert(this->fds.end(), tmp.begin(), tmp.end());
	}
	return (0);
}

void Server::handle_commands(it_user &user)
{
	const std::string msg = user->second.get_buffer();
	const std::string command_name = msg.substr(0, msg.find_first_of(" "));
	if (command_name.compare("CAP") == 0 || command_name.compare("PRIVMSG") == 0)
		return ;
	const size_t command_name_len = command_name.length();

	ACommand * command = this->_commands.at(command_name);

	command->set_args(msg.substr(command_name_len, msg.length() - command_name_len));
	command->set_user(user);
	command->run();
}

bool Server::find_commands(it_user user, it_fd it)
{
	int pos = 0;

	
	if ((pos = (user->second.get_buffer().find("JOIN ") )!= std::string::npos))
	{
		this->join_Channel(user);
		return(1);
	}
	else if ((pos = (user->second.get_buffer().find("NICK ") )!= std::string::npos))
	{
		std::string nick = user->second.get_name(user->second.get_buffer(), 1);
		user->second.prepare_buffer(user->second.get_buffer());
		send(user->first, user->second.get_buffer().c_str(), user->second.get_buffer().length(), 0);
		user->second.set_nick(nick);
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
		this->_clients.erase(user);
		this->fds.erase(it);
		return(1);
	}
	return(0);
}
