/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:12:34 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/04 15:28:35 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "ft_irc.hpp"
# include <arpa/inet.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <poll.h>
# include <map>
# include <User.hpp>

# define PC_IP "10.11.4.6"

typedef std::vector<pollfd>::iterator it_fd;

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
	void join_Channel(std::string buffer, int pos, int fd);
	int create_server();
	int main_loop();
	pollfd connect_client();
	int send_msg();
	int receive_msg();
	int get_fd() const;
	std::string get_message(char *buffer, int fd);
	bool find_commands(std::string buffer, it_fd fd);
	std::map<int, User> data;
	
private:

	int	active_fd;
	std::vector<pollfd> fds;
	sockaddr_in _address;


	Server();
};

#endif
