/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_Commands.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:02:16 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/10 11:37:25 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::vector<Channel>::iterator Server::check_channel(Channel &ch)
{
	std::vector<Channel>::iterator it;
	for(it = this->channel_list.begin(); it != this->channel_list.end(); it++)
		if(it->get_name() == ch.get_name())
			return(it);
	channel_list.push_back(ch);
	it = channel_list.end() - 1;
	return(it);
}

void Server::remove_from_ch(std::string ch_name, std::string &name)
{
	Channel ch;
	ch.set_name(" " + ch_name);
	name = name.substr(0, name.find_first_of("\n"));
	std::vector<Channel>::iterator it = check_channel(ch);
	it->delete_user_vec(name);
	
}

void Server::join_Channel(it_user user)
{
	std::string channel = user->second.get_buffer().substr(4, user->second.get_buffer().find_first_of("\n") - 4 - 1);
	std::cout << "Joining " << channel << " ..." << std::endl;
	std::ostringstream oss;
	oss << "JOIN " << channel << "\r\n";
	user->second.prepare_buffer(oss.str());
	send(user->first, user->second.get_buffer().c_str(), user->second.get_buffer().length(), 0);
	Channel ch;
	ch.set_name(channel);
	std::vector<Channel>::iterator it = check_channel(ch);
	if (it == this->channel_list.end()) 
	{
		this->channel_list.push_back(ch);
		it = this->channel_list.end() - 1;
	}
	it->user_list(user);
	this->send_msg(user, 1);
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