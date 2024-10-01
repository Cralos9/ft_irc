/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:12:34 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/01 14:50:41 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "ft_irc.hpp"
# include <arpa/inet.h>
# include <sys/socket.h>
# include <sys/types.h>

# define PC_IP "10.11.3.7"

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

	int create_server();
	int get_fd() const;
	
private:

	int	_fd;
	sockaddr_in _address;

	Server();
};

#endif
