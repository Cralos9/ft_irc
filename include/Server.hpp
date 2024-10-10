/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:12:34 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/10 14:34:18 by jmarinho         ###   ########.fr       */
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

class ACommand;

class Server
{
public:

	Server(int port);
	~Server();

	void join_Channel(it_user user);
	int create_server();
	int main_loop();
	void create_client(const int &fd, const std::string &hostname);
	pollfd connect_client();
	void send_msg(it_user user, int i);
	void msg_user(const int receiver_fd, User &msg_sender);
	void receive_msg(it_user user);
	bool find_commands(it_user user, it_fd it);
	std::vector<Channel>::iterator check_channel(Channel &ch);
	void close_all_fds();
	int handle_commands(it_user &user);
	it_user get_user(const std::string &nick);
	void disconnect_user(it_user &user);
	void remove_from_ch(std::string ch_name, std::string &name);

	static void	signal_handler(int signum);
	static bool should_end;

private:

	std::vector<Channel> channel_list;
	std::string _all_users;
	int	active_fd;
	std::vector<pollfd> fds;
	sockaddr_in _address;
	std::map<int, User> _clients;
	std::map<std::string, ACommand *> _commands;
};

it_fd	find_fd(std::vector<pollfd> &vec, const int fd);

#endif
