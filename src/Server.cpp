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

bool Server::should_end = false;

/* Constructors/Destructors */
Server::Server(int port) : active_fd(1)
{
	/*std::cout << "Server port Constructor" << std::endl;*/
	std::memset(&this->_address, 0, sizeof(this->_address));
	this->_address.sin_family = AF_INET;
	this->_address.sin_port = htons(port);
	this->_commands["JOIN"] = new Join(*this); //JOIN <channel>
	this->_commands["WHO"] = new Who(*this);   //who
	this->_commands["MODE"] = new Mode(*this); //MODE <channel> +/- <mode>  || MODE <channel> +/- <mode> <nickname>
	this->_commands["NICK"] = new Nick(*this); //NICK <new_name>
	this->_commands["QUIT"] = new Quit(*this); //QUIT :<msg>
	this->_commands["PRIVMSG"] = new PrivMsg(*this); // PRIVMSG <name> <msg> || PRIVMSG <channel> <msg>
	this->_commands["KICK"] = new Kick(*this); //KICK <channel> <nickname> :<reason> || KICK <channel> <nickname>
	//whois whois <nick>
	//part PART <channel> :<msg>
	//topic TOPIC <channel> || TOPIC <channel> <new_topic>
	//invite INVITE <nick> <channel>
	//pass? PASS <password>
	//ping? PING <>
	//pong? PONG <>
}

Server::~Server()
{
	for (std::map<std::string, ACommand *>::iterator it = this->_commands.begin(); it != this->_commands.end(); ++it)
		delete it->second;
	this->close_all_fds();
	std::cout << "Server Destructor" << std::endl;	
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
	this->_fds.push_back(sock);
	return (EXIT_SUCCESS);
}

void Server::close_all_fds()
{
	for (it_fd it = this->_fds.begin(); it != this->_fds.end(); it++)
		close(it->fd);
	this->_fds.erase(this->_fds.begin(), this->_fds.end());
}

pollfd Server::connect_client()
{
	pollfd		client;
	sockaddr_in	client_info;
	socklen_t	len = sizeof(client_info);

	client.fd = accept(this->_fds[0].fd, (struct sockaddr *)&client_info, &len);
	if (client.fd == -1)
		print_error("Accept Error");
	client.events = POLLIN;
	this->_clients[client.fd] = User(client.fd, inet_ntoa(client_info.sin_addr));
	this->active_fd++;
	std::cout << "New client " << this->active_fd << " connected" << std::endl;
	return (client);
}

void Server::receive_msg(User &user)
{
	int msg_bytes;
	char buffer[1024] = {0};
	msg_bytes = recv(user.get_fd(), buffer, sizeof(buffer), 0);
	if (msg_bytes == -1)
		print_error("recv Error");
	user.set_buffer(buffer);
	this->print_recv(buffer);
}

// std::vector<Channel> Server::get_all_user_chs(User &user)
// {
// 	std::vector<Channel> ch_vec;
// 	for (std::map<std::string, Channel>::iterator it = this->_channel_list.begin(); it != this->_channel_list.end(); it++)
// 	{
		
// 	}
// }

void Server::send_msg_all_users(User &msg_sender, int i)
{
	for (it_user user = this->_clients.begin(); user != this->_clients.end(); user++)
	{
		if (user->second.get_fd() != msg_sender.get_fd() && i == 0)
			send(user->first, msg_sender.get_buffer().c_str(),
				msg_sender.get_buffer().length(), 0);
		else if (i == 1)
			send(user->first, msg_sender.get_buffer().c_str(),
				msg_sender.get_buffer().length(), 0);
	}
}

void Server::send_msg_one_user(const int receiver_fd, User &msg_sender)
{
	send(receiver_fd, msg_sender.get_buffer().c_str(), msg_sender.get_buffer().length(), 0);
}

int Server::fds_loop()
{
	int tmp = this->active_fd;

/* 	for (it_fd it = this->_fds.begin(); it != this->_fds.end(); it++) {
		std::cout << "FD: " << it->fd << std::endl;
	} */
	for (int i = 0; i < tmp; i++)
	{
		if (this->_fds[i].revents == 0)
			continue;
		if (this->_fds[i].revents != POLLIN)
			print_error("Error revents");
		if (this->_fds[i].fd == this->_fds[0].fd)
			this->_fds.push_back(this->connect_client());
		else
		{
			User &user = this->_clients.at(this->_fds[i].fd);
			this->receive_msg(user);
			if (user.get_info() == 1)
				break;
			try
			{
				if (this->handle_commands(user))
					break;
			}
			catch (std::exception &e)
			{
				std::cerr << "Command Not Found" << std::endl;
			}
		}
	}
	return (0);
}

int Server::main_loop()
{
	int ret;

	while (!should_end)
	{
		ret = poll(this->_fds.data(), this->active_fd, -1);
		if (ret == -1)
		{
			if (errno == EINTR)
				continue;
			std::perror("Poll Error");
			break;
		}
		if (ret == 0)
		{
			std::cout << "Pool timeout" << std::endl;
			return (EXIT_FAILURE);
		}
		this->fds_loop();
	}
	return (0);
}

int Server::handle_commands(User &user)
{
	const std::string msg = user.get_buffer();
	const std::string command_name = msg.substr(0, msg.find_first_of(" "));
	const size_t command_name_len = command_name.length() + 1;

	ACommand * command = this->_commands.at(command_name);

	command->set_args(msg.substr(command_name_len, msg.length() - command_name_len));
	command->set_user(&user);
	if (command->run())
		return (1);
	return (0);
}

void Server::add_user_channel(User &user, Channel &channel)
{
	channel.user_list(user);
}

void Server::create_channel(User &user, const std::string &ch_name)
{
	this->_channel_list[ch_name] = Channel(ch_name);
	this->add_user_channel(user, this->_channel_list[ch_name]);
}

User *Server::get_user(const std::string &nick)
{
	it_user it;
	
	for (it = this->_clients.begin(); it != this->_clients.end()
		&& it->second.get_nick().compare(nick) != 0; it++)
		;
	return (&it->second);
}

void Server::disconnect_user(User &user)
{
	close(user.get_fd());
	this->active_fd--;
	this->_fds.erase(find_fd(this->_fds, user.get_fd()));
	this->_clients.erase(this->_clients.find(user.get_fd()));
}

it_fd find_fd(std::vector<pollfd> &vec, const int fd)
{
	it_fd it;
	for (it = vec.begin(); it->fd != fd; it++)
		;
	return (it);
}

void Server::print(const std::string &str)
{
	std::cout << GREEN << "Server: " << RESET << str << std::endl;
}

void Server::print_recv(const std::string &str)
{
	std::cout << RED << "Client: " << RESET << str;
}
