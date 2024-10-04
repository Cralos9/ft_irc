/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:12:34 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/04 17:28:28 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "ft_irc.hpp"
# include <arpa/inet.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <poll.h>
# include <User.hpp>

# define PC_IP "10.11.4.6"

typedef std::vector<pollfd>::iterator it_fd;
typedef std::map<int, User>::iterator it_user;

/* Class to create the server. It calls socket, bind and listen 

	- create_server(): gets fd from socket, then calls bind 
		and listen to make the server ready for requests
	- get_fd(): Returns the fd variable (socket fd)
*/
class Server
{
public:

	Server(int port);
	~Server();

	void use_commands(std::string command);
	void join_Channel(it_user user);
	int create_server();
	int main_loop();
	void create_client(const int &fd, const std::string &hostname);
	pollfd connect_client();
	void send_msg(it_user user);
	void receive_msg(it_user user);
	std::string get_message(char *buffer, int fd);
	bool find_commands(it_user user);
	std::map<int, User> data;
	
private:

	int	active_fd;
	std::vector<pollfd> fds;
	sockaddr_in _address;


	Server();
};

#endif
