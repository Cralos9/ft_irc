/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:12:34 by rumachad          #+#    #+#             */
/*   Updated: 2024/11/27 11:35:20 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "ft_irc.hpp"
# include <arpa/inet.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <poll.h>
# include "User.hpp"
# include "Channel.hpp"
# include "Commands.hpp"
# include <errno.h>
# include <ctime>
# include <fstream>
# include <signal.h>
# include "RPL.hpp"
# include <fcntl.h>

#define SERVER_NAME		"TresPingados"
#define NO_EVENTS		0
#define CHOTHER			141
#define CHSELF			140
#define AVAIL_MODES		"i,t,k,l,o"
#define MOTD_FILE		"3P.txt"

class ACommand;

class Server
{
public:

	Server(const int port, const std::string &password);
	~Server();

	int	create_server();
	int	main_loop();
	int	fds_loop();

	/* Handle User Functions */
	int 	connect_client();
	void	disconnect_user(User &user);
	void	send_msg_to_channel(const Channel &ch, const User &msg_sender, const int flag);
	void	send_msg_all_users(User &msg_sender);
	void	send_msg_one_user(const int receiver_fd, User &msg_sender);
	void	send_numeric(const User &user, const std::string &numeric, const std::string msg, ...);
	int		receive_msg(User &user);

	/* Handle Channel Functions */
	Channel									*create_channel(const std::string &ch_name);
	Channel									*check_channel(const std::string &ch_name);
	const std::string						channels_user_joined(User &user);
	const std::map<std::string, Channel>	&get_channels() const;
	void									delete_channel(Channel &channel);

	/* Handle Commands Functions */
	int 		handle_commands(User &user);
	int			call_command(std::string &command_name, User &user, std::deque<std::string> &params);
	ACommand	*get_command(const std::string &command_name);
	User 		*get_user(const std::string &nick);

	void				welcome_burst(User &user);
	bool				check_nickname(std::string &nickname);
	void				get_hostname();
	const std::string	&get_host() const;

	std::map<int, User>	&get_all_clients();
	const std::string	&get_password() const;

	static void	signal_handler(int signum);

	static bool should_end;

private:

	int									active_fd;
	sockaddr_in							_address;
	const std::string 					&_password;
	std::vector<pollfd> 				_fds;
	std::map<std::string, Channel>		_channel_list;
	std::map<int, User>					_clients;
	std::map<std::string, ACommand *>	_commands;
	time_t 								_server_creation_time;
	std::string							_hostname;
};

std::vector<pollfd>::iterator	find_fd(std::vector<pollfd> &vec, const int fd);
void 	print_recv(const User &user);

#endif
