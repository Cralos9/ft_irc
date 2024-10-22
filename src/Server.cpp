/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:23:16 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/22 15:41:12 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool Server::should_end = false;

/* Constructors/Destructors */
Server::Server(const int port, const std::string &password) : active_fd(1), _password(password)
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
	this->_commands["TOPIC"] = new Topic(*this); //topic TOPIC <channel> || TOPIC <channel> <new_topic>
	this->_commands["PART"] = new Part(*this); //part PART <channel> :<msg>
	_commands["WHOIS"] = new WhoIs(*this);
	//this->_commands["LIST"] = new List(*this);
	//whois whois <nick>
	//invite INVITE <nick> <channel>
	//pass? PASS <password>
	//ping? PING <>
	//pong? PONG <>

	_server_creation_time = std::time(0);
}

Server::~Server()
{
	for (std::map<std::string, ACommand *>::iterator it = this->_commands.begin(); it != this->_commands.end(); ++it)
		delete it->second;
	this->close_all_fds();
	/* std::cout << "Server Destructor" << std::endl;	*/
}

/* -------------------------------------------- */

int Server::create_server()
{
	int on = 1;
	pollfd sock;

					/* CREATE A SOCKET */
	sock.fd = socket(this->_address.sin_family, SOCK_STREAM, 0);
	if (sock.fd == -1)
		print_error("Socket Error");
	if (setsockopt(sock.fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)))
		print_error("setsockopt Error");

					/* BIND SOCKET TO PORT */
	if (bind(sock.fd, (struct sockaddr *)&this->_address, 
				sizeof(this->_address)) != 0)
		print_error("Bind Error");

					/* LISTEN FOR CONNECTIONS */
	if (listen(sock.fd, 5) == -1)
		print_error("Listen Error");

	sock.events = POLLIN;
	this->_fds.push_back(sock);
	std::cout << GREEN << "	////////////////////" << RESET << std::endl;
	std::cout << GREEN << "	Server is Now Online" << RESET << std::endl;
	std::cout << GREEN << "	////////////////////" << RESET << std::endl;
	return (EXIT_SUCCESS);
}

void Server::close_all_fds()
{
	for (it_fd it = this->_fds.begin(); it != this->_fds.end(); it++)
		close(it->fd);
	this->_fds.erase(this->_fds.begin(), this->_fds.end());
}

int Server::connect_client()
{
	pollfd		client;
	sockaddr_in	client_info;
	socklen_t	len = sizeof(client_info);

	client.fd = accept(this->_fds[0].fd, (struct sockaddr *)&client_info, &len);
	if (client.fd == -1)
		print_error("Accept Error");
/* 	sleep(1); */
	client.events = POLLIN;
	client.revents = NO_EVENTS;
	this->_clients[client.fd] = User(client.fd, inet_ntoa(client_info.sin_addr));
	this->active_fd++;
	this->_fds.push_back(client);
	/*GOING TO CHECK FOR PASSWORD AND SEND WELCOME MESSAGE TO NEW CLIENT*/

	receive_msg(_clients[client.fd]);
	_clients[client.fd].get_info();
	
	if (_clients[client.fd]._get_auth())
	{
		if (!check_password(_clients[client.fd]))  //check if User password matches Server Password
		{
			std::cout << RED << "Password Error" << RESET << std::endl;
			disconnect_user(_clients[client.fd]);
			return EXIT_FAILURE;
		}
		else
		{
			std::cout << GREEN << "Password Accepted" << RESET << std::endl;
			welcome_message(_clients[client.fd]); //Send welcome message to user
			_clients[client.fd]._set_auth(false);
		}
	}
	std::cout << "New client " << this->active_fd << " connected" << std::endl;
	return EXIT_SUCCESS;
}

void Server::receive_msg(User &user)
{
	int msg_bytes;
	char buffer[1024] = {0};
	msg_bytes = recv(user.get_fd(), buffer, sizeof(buffer), 0);
	
	if (msg_bytes < 0)
		print_error("recv Error");
	
	user.set_buffer(buffer);
	this->print_recv(buffer);
}

void Server::send_msg_all_users(User &msg_sender)
{
	for (it_user user = this->_clients.begin(); user != this->_clients.end(); user++)
	{
		send(user->first, msg_sender.get_buffer().c_str(),
			msg_sender.get_buffer().length(), 0);
	}
}

void Server::send_msg_to_channel(const Channel &ch, const User &msg_sender, const int flag)
{
	const std::map<User *, int> &ch_users = ch.get_users();

	for (std::map<User *, int>::const_iterator it = ch_users.begin(); it != ch_users.end(); it++) {
		if (flag == CHOTHER && msg_sender.get_fd() != it->first->get_fd())
			send(it->first->get_fd(), msg_sender.get_buffer().c_str(),
				msg_sender.get_buffer().length(), 0);
		else if (flag == CHSELF)
			send(it->first->get_fd(), msg_sender.get_buffer().c_str(),
				msg_sender.get_buffer().length(), 0);
	}
}

void Server::send_msg_one_user(const int receiver_fd, User &msg_sender)
{
	send(receiver_fd, msg_sender.get_buffer().c_str(), msg_sender.get_buffer().length(), 0);
}

bool	Server::check_password(User &user)
{
/* 	std::cout << RED << "Client Password:" << user.get_password() << std::endl;
	std::cout << "Server Password:" << _password << RESET << std::endl; */
	if (_password == user.get_password())
		return true;
	return false;
}

void Server::welcome_message(User &user)
{
    std::string msg01 = ":" + user.get_hostname() + " " + RPL_WELCOME + " " + user.get_nick() + " :" + "Welcome to the " + SERVER_NAME + " IRC Network, " + user.get_nick() + "!" + "\r\n";
    std::string msg02 = ":" + user.get_hostname() + " " + RPL_YOURHOST + " " + user.get_nick() + " :" + "Your host is " + user.get_hostname() + ", running version v1.0" + "\r\n";
    std::string msg03 = ":" + user.get_hostname() + " " + RPL_CREATED + " " + user.get_nick() + " :" + "This server was created " + std::asctime(std::localtime(&_server_creation_time));
    std::string msg04 = ":" + user.get_hostname() + " " + RPL_MYINFO + " " + user.get_nick() + " " + user.get_hostname() + " v1.0 o iklt\r\n";

    send(user.get_fd(), msg01.c_str(), msg01.length(), 0);
    send(user.get_fd(), msg02.c_str(), msg02.length(), 0);
    send(user.get_fd(), msg03.c_str(), msg03.length(), 0);
    send(user.get_fd(), msg04.c_str(), msg04.length(), 0);
}


int Server::fds_loop()
{
	int tmp = this->active_fd;

	for (int i = 0; i < tmp; i++)
	{
		if (this->_fds[i].revents == NO_EVENTS)
			continue;
		if (this->_fds[i].revents != POLLIN)
			print_error("Error revents");
		if (this->_fds[i].fd == this->_fds[0].fd)
		{
			if (this->connect_client())
				break;	
		}
		else
		{
			User &user = this->_clients.at(this->_fds[i].fd);
			this->receive_msg(user);
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
	std::string command_name = msg.substr(0, msg.find_first_of(" "));
	const size_t command_name_len = command_name.length() + 1;

	//if (command_name.find_first_of("\r\n"))
	command_name = command_name.substr(0, command_name.find_first_of("\r"));
	ACommand * command = this->_commands.at(command_name);

	//if (command_name != "LIST")
	command->set_args(msg.substr(command_name_len, msg.length() - command_name_len));
	command->set_user(&user);
	command->run();
	return (0);
}

/* Channel Functions */
const std::string Server::channels_user_joined(User &user)
{
	std::string user_joined_ch;

	for (it_ch it = _channel_list.begin(); it != _channel_list.end(); it++)
	{
		if (it->second.is_user_on_ch(user) == 1)
			user_joined_ch.append(it->first + " ");
	}
	return (user_joined_ch);
}

Channel *Server::check_channel(const std::string &ch_name)
{
	it_ch it = this->_channel_list.find(ch_name);
	if (it == this->_channel_list.end())
		return (NULL);
	return (&it->second);
}

Channel *Server::create_channel(const std::string &ch_name)
{
	this->_channel_list[ch_name] = Channel(ch_name);
	return (&this->_channel_list[ch_name]);
}
/* End Channel Functions */

User *Server::get_user(const std::string &nick)
{
	it_user it;
	
	for (it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		if (it->second.get_nick().compare(nick) == 0)
			return (&it->second);
	}
	return (NULL);
}

void Server::disconnect_user(User &user)
{
	const int fd = user.get_fd();

	close(fd);
	this->active_fd--;
	this->_clients.erase(this->_clients.find(fd));
	this->_fds.erase(find_fd(this->_fds, fd));
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
	std::cout << RED << "Client BUFFER:\n" << BLUE << str << RESET;
}
