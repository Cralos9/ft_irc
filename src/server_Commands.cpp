/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_Commands.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:02:16 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/04 14:01:47 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::join_Channel(std::string buffer, int pos, int fd)
{
	for(std::map<User, pollfd>::iterator it = this->data.begin(); it != this->data.end(); it++)
	{
		std::string channel = buffer.substr(pos, (buffer.find_first_of("\n") - pos - 1));
	
		if (it->second.fd == fd)
		{
			std::cout << "Joining " << channel << " ..." << std::endl;
			std::ostringstream oss; 
			oss << ":" << it->first._nick << "!" << it->first._nick << "@localhost JOIN " << channel << "\r\n"; 
			std::string join_msg = oss.str();
			send(fd, join_msg.c_str(), join_msg.length(), 0);
		}
	}

   /* // Send the topic message (if no topic is set)
	std::string topic_msg = ":irc.myserver.com 331 cacarval #general :No topic is set\r\n";
	send(fd, topic_msg.c_str(), topic_msg.length(), 0);

	// Send the names list (for now, only including the joining user)
	std::string names_msg = ":irc.myserver.com 353 cacarval = #general :cacarval\r\n";
	send(fd, names_msg.c_str(), names_msg.length(), 0);

	// Send the end of names list
	std::string end_names_msg = ":irc.myserver.com 366 cacarval #general :End of /NAMES list.\r\n";
	send(fd, end_names_msg.c_str(), end_names_msg.length(), 0);*/
}
