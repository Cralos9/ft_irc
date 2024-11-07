/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:23:16 by rumachad          #+#    #+#             */
/*   Updated: 2024/11/07 15:22:25 by cacarval         ###   ########.fr       */
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
	this->_commands["JOIN"] = new Join(*this, false);			//JOIN <channel>
	this->_commands["who"] = new Who(*this, false);			//WHO <mask>
	this->_commands["MODE"] = new Mode(*this, false);			//MODE <channel> +/- <mode>  || MODE <channel> +/- <mode> <nickname>
	this->_commands["NICK"] = new Nick(*this, true);			//NICK <new_name>
	this->_commands["QUIT"] = new Quit(*this, true);			//QUIT :<msg>
	this->_commands["PRIVMSG"] = new PrivMsg(*this, false);	//PRIVMSG <name> <msg> || PRIVMSG <channel> <msg>
	this->_commands["KICK"] = new Kick(*this, false);			//KICK <channel> <nickname> :<reason> || KICK <channel> <nickname>
	this->_commands["TOPIC"] = new Topic(*this, false);		//TOPIC <channel> || TOPIC <channel> <new_topic>
	this->_commands["PART"] = new Part(*this, false);
	this->_commands["LIST"] = new List(*this, false);
	this->_commands["INVITE"] = new Invite(*this, false);		//INVITE <nick> <channel>
	this->_commands["WHOIS"] = new WhoIs(*this, false);
	this->_commands["PASS"] = new Pass(*this, true);
/* 	this->_commands["PONG"] = new Ping(*this); */
	this->_commands["PING"] = new Pong(*this, true);
	this->_commands["USER"] = new UserCMD(*this, true);
	//this->_commands["LIST"] = new List(*this);
	//pass? PASS <password>
	//pong? PONG <>

	_server_creation_time = std::time(0);
	get_hostname();
}

Server::~Server()
{
	for (std::map<std::string, ACommand *>::iterator it = this->_commands.begin(); it != this->_commands.end(); ++it)
		delete it->second;
	this->close_all_fds();
	/* std::cout << "Server Destructor" << std::endl;	*/
}

/* -------------------------------------------- */

void Server::get_hostname()
{
	// Gets the hostname from /etc/hostname
	std::ifstream hostnameFile("/etc/hostname");
	if (!hostnameFile)
	{
		std::cerr << "Error opening /etc/hostname" << std::endl;
		_hostname = "localhost";
		return;
	}

	std::string hostname;
	std::getline(hostnameFile, hostname);
	_hostname = hostname;
}

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
	client.events = POLLIN;
	client.revents = NO_EVENTS;
	this->_clients[client.fd].error_flag = 0;
	this->_clients[client.fd] = User(client.fd, inet_ntoa(client_info.sin_addr));
	this->active_fd++;
	this->_fds.push_back(client);

	std::cout << "New Client: " << active_fd << " connected" << std::endl;
	return EXIT_SUCCESS;
}

void Server::channel_list(User &user)
{
	for(std::map<std::string, Channel>::iterator it = _channel_list.begin(); it != _channel_list.end(); it++)
	{
		std::stringstream size_as_str;
		size_as_str << it->second.get_user_map_size();
		std::string response = ":" + user.get_hostname() + " 322 " + user.get_nick() + " " + it->second.get_name() + " " \
			+ size_as_str.str() + " " + it->second.get_topic() + "\r\n";
		user.set_buffer(response);
		send_msg_one_user(user.get_fd(), user);
	}
}

int Server::receive_msg(User &user)
{
	int msg_bytes;
	char buffer[1024] = {0};
	msg_bytes = recv(user.get_fd(), buffer, sizeof(buffer), 0);
	
	if (msg_bytes <= 0)
	{
		this->disconnect_user(user);
		return (1);
	}
	user.set_buffer(buffer);
	this->print_recv(buffer);
	return(0);         
}

void Server::send_numeric(const User &user, const std::string &numeric,
							const std::string msg, ...)
{
	std::string rpl = ":" + _hostname + " " + numeric + " " + user.get_nick() + " ";

	std::va_list params;
	va_start(params, msg);
	for (std::string::const_iterator it = msg.begin(); it != msg.end(); it++) {
		if (*it == '%')
		{
			rpl.append(va_arg(params, const char *));
			it++;
		}
		else
			rpl += *it;
	}
	rpl.append("\r\n");
	print(rpl);
	send(user.get_fd(), rpl.c_str(), rpl.length(), 0);
}


void Server::send_msg_all_users(User &msg_sender)
{
	print(msg_sender.get_buffer());
	for (it_user user = this->_clients.begin(); user != this->_clients.end(); user++)
	{
		send(user->first, msg_sender.get_buffer().c_str(),
			msg_sender.get_buffer().length(), 0);
	}
}

void Server::send_msg_to_channel(const Channel &ch, const User &msg_sender, const int flag)
{
	const std::map<User *, int> &ch_users = ch.get_users();

	print(msg_sender.get_buffer());
	for (std::map<User *, int>::const_iterator it = ch_users.begin(); it != ch_users.end(); it++) 
	{
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
	print(msg_sender.get_buffer());
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
	std::string time = std::asctime(std::localtime(&_server_creation_time));

	time[time.find('\n')] = '\0';
	send_numeric(user, RPL_WELCOME, ":Welcome to the " SERVER_NAME " IRC Network, %s!",
					user.get_nick().c_str());
	send_numeric(user, RPL_YOURHOST, ":Your host is %s running version v1.0",
					user.get_hostname().c_str());
	send_numeric(user, RPL_CREATED, ":This server was created %s", time.c_str());
	send_numeric(user, RPL_MYINFO, "localhost v1.0 o iklt");
	send_numeric(user, RPL_ISUPPORT, "CHANMODES=b,k,l,imnpst");
	send_numeric(user, RPL_MOTDSTART, ":- %s Message of the day -", _hostname.c_str());
	send_numeric(user, RPL_MOTD, ":- Jose Figueiras is innocent 🇵🇹");
	send_numeric(user, RPL_ENDOFMOTD, ":End of /MOTD");
	user.welcome_flag = true;
}

bool Server::check_nickname(std::string &nickname)
{
	for (it_user it = _clients.begin(); it != _clients.end(); it++)
		if (it->second.get_nick() == nickname)
			return(1);
	return(0);
}

void Server::send_error(User &user)
{
	std::string reply;
	if (user.error_flag == 1)
	{
		reply = client_rpl(user.get_hostname(), user.get_nick(), "464");
		reply = reply + " Wrong Password\r\n";
	 	user.set_buffer(reply);
	}
	else if (user.error_flag == 2)
	{
		reply = client_rpl(user.get_hostname(), "*", "433");
		reply = reply + user.get_nick() + " :Nickname already in use\r\n";
	 	user.set_buffer(reply);
	}
	else if (user.error_flag == 3)
	{
	
		reply = client_rpl(user.get_hostname(), "*", "432");
		reply = reply + user.get_nick() + " :Erroneus nickname\r\n";
	 	user.set_buffer(reply);
	}
	send_msg_one_user(user.get_fd(), user);
	user.error_flag = 0;
}

int Server::fds_loop()
{
	int tmp = this->active_fd;

	for (int i = 0; i < tmp; i++)
	{
		if (this->_fds[i].revents == NO_EVENTS)
			continue;
		if (!(_fds[i].revents & POLLIN) && !(_fds[i].revents & POLLOUT))
		{
			std::cout << _fds[i].revents << std::endl;
			print_error("Error revents");
		}
		if (this->_fds[i].fd == this->_fds[0].fd)
			this->connect_client();
		else
		{
			User &user = this->_clients.at(this->_fds[i].fd);
			if (this->_fds[i].revents & POLLIN)
			{
				if (this->receive_msg(user))
					return(1);
				this->_fds[i].events |= POLLOUT;
			}
			else if (this->_fds[i].revents & POLLOUT)
			{
				this->handle_commands(user);
				if (user.error_flag == 0 && !(user.get_username()).empty())
					user._set_auth(false);
				else
				{
					if (user.error_flag != 0)
						send_error(user);
					this->_fds[i].events = POLLIN;
					return(1);
				}
				if (user._get_auth() == false && user.welcome_flag == false)
					welcome_message(user);
				// user.erase_buffer();
				this->_fds[i].events = POLLIN;
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

void Server::handle_commands(User &user)
{
	ACommand *command = NULL;
	std::vector<std::string> lines = split_lines(user.get_buffer());

	for(std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); it++)
	{
		try
		{
			std::vector<std::string> split = parse_split(*it);
			command = _commands.at(split[0]);
			command->set_args(split);
			command->set_user(&user);
			command->check();
			command->run();
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
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
	this->active_fd--;
	this->_fds.erase(find_fd(this->_fds, fd));
	close(fd);

	for(std::map<std::string, Channel>::iterator it = _channel_list.begin(); it != _channel_list.end();)
	{
		if(it->second.is_user_on_ch(user))
		{
			it->second.delete_user_vec(user);
			if (it->second.get_user_map_size() == 0)
			{
				std::map<std::string, Channel>::iterator temp = it;
				it++;
				_channel_list.erase(temp);
				continue ;
			}
		}
		it++;
	}
	this->_clients.erase(this->_clients.find(fd));
}

std::map<int, User>& Server::get_all_clients()
{
	return _clients;
}