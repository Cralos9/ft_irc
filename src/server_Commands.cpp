/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_Commands.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:02:16 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/04 17:28:59 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::join_Channel(it_user user)
{
	std::cout << "User " << user->second.get_nick() << std::endl;
	std::string channel = user->second.get_buffer().substr(4, user->second.get_buffer().find_first_of("\n") - 4 - 1);
	std::cout << "Joining " << channel << " ..." << std::endl;
	std::cout << user->second.get_nick() << std::endl;
	std::ostringstream oss; 
	oss << "JOIN" << channel << "\r\n";
	user->second.prepare_buffer(oss.str());
	std::cout << user->second.get_buffer() << std::endl;
	send(user->first, user->second.get_buffer().c_str(), user->second.get_buffer().length(), 0);
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
