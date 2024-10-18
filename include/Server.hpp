/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:12:34 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/18 12:18:37 by rumachad         ###   ########.fr       */
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
#include <ctime>

#define RPL_WELCOME		"001"
#define RPL_YOURHOST	"002"
#define RPL_CREATED		"003"
#define RPL_MYINFO		"004"
#define RPL_ISUPPORT	"005"
#define SERVER_NAME		"TresPingados"
#define NO_EVENTS		0
#define CHSELF			140
#define CHOTHER			141

typedef std::vector<pollfd>::iterator it_fd;
typedef std::map<int, User>::iterator it_user;
typedef std::map<std::string, Channel>::iterator it_ch;

class ACommand;

class Server
{
public:

	Server(const int port, const std::string &password);
	~Server();

	void 		join_Channel(it_user user);
	int			create_server();

	int 		main_loop();
	int 		fds_loop();

	int 		connect_client();
	void		send_msg_to_channel(const Channel &ch, const User &msg_sender, const int flag);
	void		send_msg_all_users(User &msg_sender);
	void 		send_msg_one_user(const int receiver_fd, User &msg_sender);
	void 		receive_msg(User &user);

	Channel 	*create_channel(const std::string &ch_name);
	Channel 	*check_channel(const std::string &ch_name);

	int 		handle_commands(User &user);
	User 		*get_user(const std::string &nick);
	
	void		 disconnect_user(User &user);
	void 		close_all_fds();

	void 		print(const std::string &str);
	void 		print_recv(const std::string &str);

	static void	signal_handler(int signum);
	static bool should_end;

	bool		check_password(User &user);
	void		welcome_message(User &user);

	
private:

	int									active_fd;
	sockaddr_in							_address;
	const std::string 					&_password;
	std::vector<pollfd> 				_fds;
	std::map<std::string, Channel>		_channel_list;
	std::map<int, User>					_clients;
	std::map<std::string, ACommand *>	_commands;
	time_t 								_server_creation_time;
};

it_fd			find_fd(std::vector<pollfd> &vec, const int fd);

#endif
