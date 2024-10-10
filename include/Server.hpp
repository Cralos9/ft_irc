/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:12:34 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/10 11:36:42 by cacarval         ###   ########.fr       */
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

typedef std::vector<pollfd>::iterator it_fd;
typedef std::map<int, User>::iterator it_user;

/* Class to create the server. It calls socket, bind and listen 

	- create_server(): gets fd from socket, then calls bind 
		and listen to make the server ready for requests
	- get_fd(): Returns the fd variable (socket fd)
*/
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
	void receive_msg(it_user user);
	bool find_commands(it_user user, it_fd it);
	std::vector<Channel>::iterator check_channel(Channel &ch);
	void close_all_fds();
	void handle_commands(it_user &user);
	void remove_from_ch(std::string ch_name, std::string &name);

private:

	std::vector<Channel> channel_list;
	std::string _all_users;
	int	active_fd;
	std::vector<pollfd> fds;
	sockaddr_in _address;
	std::map<int, User> _clients;
	std::map<std::string, ACommand *> _commands;
};

#endif
