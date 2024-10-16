/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:12:34 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/15 17:08:08 by rumachad         ###   ########.fr       */
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
# include <signal.h>
# include <cerrno>
# include <errno.h>

typedef std::vector<pollfd>::iterator it_fd;
typedef std::map<int, User>::iterator it_user;
typedef std::map<std::string, Channel>::iterator it_ch;

class ACommand;

class Server
{
public:

	Server(int port);
	~Server();

	void join_Channel(it_user user);
	int create_server();

	int main_loop();
	int fds_loop();

	pollfd connect_client();
	void send_msg_all_users(User &msg_sender, int i);
	void send_msg_one_user(const int receiver_fd, User &msg_sender);
	void receive_msg(User &user);

	void create_channel(User &user, const std::string &ch_name);
	void add_user_channel(User &user, Channel &channel);
	void remove_from_ch(Channel &ch, User &user);
	Channel *check_channel(const std::string &ch_name);

	int handle_commands(User &user);
	User *get_user(const std::string &nick);
	
	void disconnect_user(User &user);
	void close_all_fds();

	void print(const std::string &str);
	void print_recv(const std::string &str);

	static void	signal_handler(int signum);
	static bool should_end;

private:

	std::string _all_users;
	int	active_fd;
	std::vector<pollfd> _fds;
	sockaddr_in _address;
	std::map<std::string, Channel> _channel_list;
	std::map<int, User> _clients;
	std::map<std::string, ACommand *> _commands;
};

it_fd	find_fd(std::vector<pollfd> &vec, const int fd);

#endif
